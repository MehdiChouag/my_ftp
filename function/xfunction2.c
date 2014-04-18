/*
** xfunction2.c for xfunction2 in /home/chouag_m/rendu/TCP/function
** 
** Made by Mehdi Chouag
** Login   <chouag_m@epitech.net>
** 
** Started on  Thu Apr 10 00:34:32 2014 Mehdi Chouag
** Last update Thu Apr 10 00:48:25 2014 Mehdi Chouag
*/

#include "client.h"

void	*xmalloc(size_t size)
{
  void	*ret;

  if ((ret = malloc(size)) != NULL)
    return (ret);
  fprintf(stderr, "Can't allocate the pointer");
  exit(EXIT_FAILURE);
}

void	xfree(void *ptr)
{
  if (ptr != NULL)
    free(ptr);
  else
    fprintf(stderr, "The pointer is already NULL\n");
}
