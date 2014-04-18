##
## Makefile for  in /home/aube_a/Documents/projet/thread
## 
## Made by Mehdi Chouag
## Login   <aube_a@epitech.net>
## 
## Started on  Tue Mar 18 23:25:23 2014 Mehdi Chouag
## Last update Thu Apr 10 19:40:39 2014 Mehdi Chouag
##

SRCC		= Client/src/client.c \
		  function/xfunction.c \
		  function/check_command.c \
		  function/my_str_to_wordtab.c \
		  Client/src/getfile.c \
		  function/xfunction2.c \
		  Client/src/verif.c


SRCS		= Server/src/serveur.c \
		  function/xfunction.c \
		  function/check_command.c \
		  Server/src/get.c \
		  function/my_str_to_wordtab.c \
		  function/xfunction2.c 

OBJ1		= $(SRCC:.c=.o)
OBJ2		= $(SRCS:.c=.o)

CFLAGS		= -W -Wall -Wextra -Werror -I ./Client/header/ -I ./Server/header

NAMEC		= client
NAMES		= serveur

all: $(NAMES) $(NAMEC)

$(NAMEC): $(OBJ1)
	gcc -o $(NAMEC) $(OBJ1)

$(NAMES): $(OBJ2)
	gcc -o $(NAMES) $(OBJ2)

clean:
	rm -f $(OBJ1)
	rm -f $(OBJ2)

fclean: clean
	rm -f $(NAMEC)
	rm -f $(NAMES)

re: fclean all
