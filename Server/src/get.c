/*
** get.c for get.c in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Apr  9 16:33:56 2014 Mehdi Chouag
** Last update Sun Apr 13 23:09:29 2014 Mehdi Chouag
*/

#include "serveur.h"

void		send_len(int len, t_server *s)
{
  sprintf(s->sizef, "%d\n", len);
  write(s->socket, s->sizef, 128);
  memset(s->sizef, '\0', 128);
}

int		check_path(char *str, char *path)
{
  char		buff[PATH_MAX];

  realpath(str, buff);
  fprintf(stderr, "%d\n", strncmp(buff, path, strlen(path)));
  if (strncmp(path, buff, strlen(path)) == 0)
    return (0);
  return (-1);
}

void		getfile(char **tab, t_server *s)
{
  struct stat	t;
  int		fd;
  char		*str;
  char		path[PATH_MAX];

  realpath(tab[1], path);
  fd = open(path, O_RDONLY);
  stat(path, &t);
  if ((t.st_mode & S_IFDIR)
      || (int)t.st_size == 0 || check_path(path, s->homepath) == -1)
    {
      write(s->socket, "0\n", 2);
      write(s->socket, "Can't get the file\n", 19);
    }
 else
    {
      send_len((int)t.st_size, s);
      str = xmalloc(sizeof(char) * (int)t.st_size);
      read(fd, str, (int)t.st_size);
      write(s->socket, str, (int)t.st_size);
      xfree(str);
    }
  close(fd);
}
