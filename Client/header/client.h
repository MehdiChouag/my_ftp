/*
** header.h for header in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Wed Mar 26 18:16:45 2014 Mehdi Chouag
** Last update Sun Apr 13 23:07:18 2014 Mehdi Chouag
*/

#ifndef HEADER_H_
# define HEADER_H_

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
# include <signal.h>
# include <limits.h>

# define NB_CLIENT 10
# define PROTOCOL "TCP"
# define HOME "./fserver"

typedef struct		s_client
{
  struct protoent	*pr;
  struct sockaddr_in	sin;
  int			fd;
  int			socket;
  int			port;
  char			*homepath;
  int			ret;
  FILE			*get;
  int			len;
  char			buff[4096];
}			t_client;

int			xsocket(int domain, int type, int protocol);
int			xconnect(int sockfd, struct sockaddr_in *addr, socklen_t addrlen);
void			init_client(t_client *c, char *ip);
int			check_cmd(char *str);
int			check_cd(char *str);
int			check_put(char *str);
void			my_putstr(char *str);
char			**my_str_to_wordtab(char *str, char c);
void			getfile(t_client *c, char **cmd);
void			handle(int i);
void			xfree(void *ptr);
void			*xmalloc(size_t size);
void			putfile(char **tab, int cs);
int			check_path(char *str);
void			check_dir(int i, char *dir, char *file);
char			*path(char **cmd);
void			read_server(t_client *c, int *j, char **cmd);
char			**connect_client(int cs, char *str, int *i);
FILE			*openfile(t_client *c, char **cmd, int *len);
void			getfile(t_client *c, char **cmd);
void			handle(int i);

#endif /* !HEADER_H_ */ 
