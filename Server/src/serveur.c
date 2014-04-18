/*
** main.c for main.c in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Mar 26 12:12:43 2014 Mehdi Chouag
** Last update Fri Apr 18 13:36:59 2014 Mehdi Chouag
*/

#include "serveur.h"

void			change_dir(char **tab, char *homepath, int cs)
{
  char			buff[PATH_MAX];
  char			*path;

  path = NULL;
  path = getcwd(path, 4096);
  if (strcmp(tab[1], "") != 0)
    {
      realpath(tab[1], buff);
      if (strncmp(homepath, buff, strlen(homepath)) ==  0)
	{
	  if (chdir(tab[1]) == -1)
	    write(cs, "No such or directory\n", 21);
	  else
	    write(cs, "New directory\n", 14);
	}
      else
	write(cs, "You cannot access to this directory\n", 36);
    }
  else
    {
      chdir(homepath);
      write(cs, "New directory\n", 14);
    }
  memset(buff, '\0', PATH_MAX);
  memset(path, '\0', strlen(path));
}

void			read_cmd(char *str, t_server *s)
{
  char			**tab;

  tab = my_str_to_wordtab(str, ' ');
  if (!check_cmd(str))
    {
      if (!strcmp(str, "ls"))
	system("ls -l --color");
      else
	system(str);
   }
  else if (!check_cd(tab[0]))
    change_dir(tab, s->homepath, s->socket);
  else if (!check_put(tab[0]))
    getfile(tab, s);
  else
    write(s->socket, "Invalid Command\n", 16);
}

void			connect_client(t_server *s)
{
  char			buff[4096];
  int			oldfd;

  read(s->socket, buff, 4096);
  oldfd = dup(1);
  dup2(s->socket, 1);
  read_cmd(buff, s);
  dup2(oldfd, 1);
  fflush(stdout);
  memset(buff, '\0', 4096);
}

void			init_socket(t_server *s)
{
  int			opt;
  char			*path;

  path = NULL;
  path = getcwd(path, 4096);
  opt = 1;
  s->pr = getprotobyname(PROTOCOL);
  s->fd = xsocket(AF_INET, SOCK_STREAM, s->pr->p_proto);
  setsockopt(s->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  s->sin.sin_family = AF_INET;
  s->sin.sin_port = htons(s->port);
  s->sin.sin_addr.s_addr = INADDR_ANY;
  xbind(s->fd, &(s->sin), sizeof(s->sin));
  xlisten(s->fd, NB_CLIENT);
  s->size = sizeof(s->sin_client);
  s->homepath = strcat(path, "/fserver"); 
  if (chdir(s->homepath) == -1)
    {
      fprintf(stderr, "Need fserver directory in your current directory\n");
      exit(EXIT_FAILURE);
    }
}

int			main(int ac, char **av)
{
  t_server		s;
  pid_t			pid;

  if (ac != 2)
    {
      fprintf(stderr, "Usage: ./serveur [port]\n");
      return (-1);
    }
  s.port = atoi(av[1]);
  init_socket(&s);
  while (42)
    {
      s.socket = xaccept(s.fd, &(s.sin_client), &s.size);
      write(s.socket, "\033[0;0;32mYou are connected\033[0m\n", 38);
      printf("NEW CLIENT CONNECTED\n");
      if ((pid = fork()) == 0)
	{
	  close(s.fd);
	  while (42)
	    connect_client(&s);
	}
      close(s.socket);
    }
  return (0);
}
