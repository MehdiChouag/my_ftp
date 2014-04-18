/*
** main.c for main.c in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Mar 26 12:12:43 2014 Mehdi Chouag
** Last update Fri Apr 18 13:36:43 2014 Mehdi Chouag
*/

#include "client.h"

void			read_server(t_client *c, int *j, char **cmd)
{
  char			buff[4096];
  int			ret;
  int			z;

  z = 0;
  if (!(*j))
    {
      if (!strcmp(cmd[0], "get") && strcmp(cmd[1], ""))
	getfile(c, cmd);
      else
	{
	  while (z == 0 && (ret = read(c->fd, buff, 4096)) > 0)
	    {
	      if (ret < 4096)
		z = -1;
	      printf("%s", buff);
	      memset(buff, '\0', 4096);
	    }
	}
      free(cmd);
    }
}

char			**connect_client(int cs, char *str, int *i)
{
  char			**tab;

  *i = -1;
  tab = my_str_to_wordtab(str, ' ');
  str[strlen(str) - 1] = '\0';
  if (check_cmd(str) == 0 || check_cd(tab[0]) == 0 
      || check_put(tab[0]) == 0)
    {
      write(cs, str, strlen(str));
      *i = 0;
    }
  else if (strcmp("quit", str) == 0)
    *i = 42;
  else
    my_putstr("Command invalid\n");
  memset(str, '\0', 4096);
  return (tab);
}

void			init_client(t_client *c, char *ip)
{
  int			opt;
  char			*path;

  opt = 1;
  path = NULL;
  path = getcwd(path, 4096);
  c->pr = getprotobyname(PROTOCOL);
  c->fd = xsocket(AF_INET, SOCK_STREAM, c->pr->p_proto);
  setsockopt(c->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  c->sin.sin_family = AF_INET;
  c->sin.sin_port = htons(c->port);
  c->sin.sin_addr.s_addr = inet_addr(ip);
  xconnect(c->fd, &(c->sin), (socklen_t)sizeof(c->sin));
  signal(SIGINT, handle);
  signal(SIGQUIT, handle);
  c->homepath = strcat(path, "/fclient");
  if (chdir(c->homepath) == -1)
    {
      fprintf(stderr, "Need fclient directory in your current directory\n");
      exit(EXIT_FAILURE);
    }
}

int			main(int ac, char **av)
{
  t_client		c;
  char			buff[4096];
  int			i;
  char			**cmd;

  i = -1;
  if (ac != 3)
    {
      fprintf(stderr, "Usage : ./client machine port\n");
      return (-1);
    }
  c.port = atoi(av[2]);
  init_client(&c, av[1]);
  read(c.fd, buff, 4096);
  my_putstr(buff);
  memset(buff, '\0', 4096);
  while (i != 42)
    {
      write(0, "$> ", 3);
      read(0,  buff, 4096);
      cmd = connect_client(c.fd, buff, &i);
      read_server(&c, &i, cmd);
    }
  printf("\033[0;0;31mYou are disconnected\033[0m\n");
  return (0);
}
