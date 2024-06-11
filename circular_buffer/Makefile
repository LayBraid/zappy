##
## EPITECH PROJECT, 2021
## makefile
## File description:
## Makefile
##

CC	=	gcc

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -g3

INCLUDE	=	-Iinclude
CFLAGS 	+= $(INCLUDE)

NAME	=	libcirc_buff.a

all:	$(OBJ)
		ar rc $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:	fclean all