/*
** check_command.c for Check_command in /home/chouag_m/rendu/TCP
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Mon Apr  7 16:08:43 2014 Mehdi Chouag
** Last update Wed Apr  9 11:41:31 2014 Mehdi Chouag
*/

#include "client.h"

int	check_cmd(char *str)
{
  if (strcmp(str, "ls") == 0 || strcmp(str, "pwd") == 0)
    return (0);
  return (-1);
}

int	check_put(char *str)
{
  if (strcmp(str, "put") == 0 || strcmp(str, "get") == 0)
    return (0);
  return (-1);
}

int	check_cd(char *str)
{
  if (strcmp(str, "cd") == 0)
    return (0);
  return (-1);
}

void	my_putstr(char *str)
{
  int	i;

  i = -1;
  while (str[++i])
    write(1, &str[i], 1);
}
