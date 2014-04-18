/*
** header.h for header in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Mar 26 18:16:45 2014 Mehdi Chouag
** Last update Sat Apr 12 00:47:27 2014 Mehdi Chouag
*/

#ifndef SERVEUR_H_
# define SERVEUR_H_

# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <netdb.h>
# include <stdio.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

# define NB_CLIENT 10
# define PROTOCOL "TCP"

typedef struct		s_server
{
  struct protoent	*pr;
  struct sockaddr_in	sin_client;
  struct sockaddr_in	sin;
  int			fd;
  int			socket;
  socklen_t		size;
  int			port;
  char			*homepath;
  struct stat		t;
  int			file;
  char			*send;
  char			sizef[128];
}			t_server;

int			xbind(int sockfd, struct sockaddr_in *addr, socklen_t addrlen);
int			xsocket(int domain, int type, int protocol);
int			xaccept(int sockfd, struct sockaddr_in *addr ,socklen_t *len);
int			xlisten(int sockfd, int backlog);
void			init_socket(t_server *s);
void			change_dir(char **tab, char *homepath, int cs);
int			check_cmd(char *str);
int			check_cd(char *str);
int			check_put(char *str);
void			my_putstr(char *str);
void			read_cmd(char *str, t_server *s);
char			**my_str_to_wordtab(char *str, char c);
void			getfile(char **tab, t_server *s);
void			*xmalloc(size_t size);
void			xfree(void *ptr);
void			send_len(int len, t_server *s);
void			putfile(char **tab, int cs);
int			check_path(char *str, char *path);
void			connect_client(t_server *s);
int			check_path(char *str, char *path);
void			getfile(char **tab, t_server *s);

#endif /* !SERVEUR_H_ */ 
