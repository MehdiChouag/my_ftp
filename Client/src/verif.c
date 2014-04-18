/*
** verif.c for verif.c in /home/chouag_m/rendu/PSU_2013_myftp
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Thu Apr 10 19:38:21 2014 Mehdi Chouag
** Last update Sun Apr 13 23:03:36 2014 Mehdi Chouag
*/

#include "client.h"

void		check_dir(int i, char *dir, char *file)
{
  char		*cur;
  char		path[PATH_MAX];

  realpath(dir, path);
  cur = NULL;
  cur = strcat(getcwd(cur, 4096), "/");
  if (i == 1 || strlen(path) < strlen(cur))
    {
      remove(strcat(cur, file));
      my_putstr("Can't get the file\n");
    }
}

char		*path(char **cmd)
{
  char		path[PATH_MAX];
  char		**tab;
  int		i;
  char		**tab2;
  int		z;
  char		*cur;

  i = -1;
  z = -1;
  cur = NULL;
  cur = getcwd(cur, 4096);
  tab2 = my_str_to_wordtab(cmd[1], '/');
  while (strcmp(tab2[++z], ""));
  while (++i < z)
    cur = strcat(strcat(cur, "/"), tab2[i]);
  i = -1;
  realpath(tab2[z - 1], path);
  tab = my_str_to_wordtab(path, '/');
  while (strcmp(tab[++i], ""));
  return (tab[i - 1]);
}
