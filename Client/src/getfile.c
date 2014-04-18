/*
** getfile.c for getfile.c in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Apr  9 18:46:33 2014 Mehdi Chouag
** Last update Sun Apr 13 23:07:06 2014 Mehdi Chouag
*/

#include "client.h"

FILE		*openfile(t_client *c, char **cmd, int *len)
{
  FILE		*fd;
  char		*dir;
  char		*cur;
  char		sizef[128];

  cur = NULL;
  cur = getcwd(cur, 4096);
  if (cur == NULL || strcmp(c->homepath, cur))
    {
      fprintf(stderr, "Need fclient Directory\n");
      exit(EXIT_FAILURE);
    }
  dir = path(cmd);
  fd = fopen(dir, "w+");
  read(c->fd, sizef, 128);
  *len = atoi(sizef);
  if (*len == 0)
    {
      remove(dir);
      my_putstr("Can't get the file\n");
    }
  return (fd);
}

void		getfile(t_client *c, char **cmd)
{
  int		i;

  i = -1;
  c->get = openfile(c, cmd, &(c->len));
  c->ret = 0; 
  while (i == -1 && c->ret != c->len)
    {
      c->ret += read(c->fd, c->buff, 4096);
      if (strcmp(c->buff, "Can't get the file\n") == 0)
        i = 1;
      fseek(c->get, 0, SEEK_END);
      fwrite(c->buff, 1, strlen(c->buff), c->get);
      fseek(c->get, SEEK_SET, 0);
      memset(c->buff, '\0', 4096);
    }
  fclose(c->get);
  check_dir(i, cmd[1], path(cmd));
  if (i != 1 && c->len)
    my_putstr("Transfert is over\n");
  memset(c->buff, '\0', 4096);
}

void		handle(int __attribute__((unused))i)
{
  my_putstr("\n$> ");
}
