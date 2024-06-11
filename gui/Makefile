##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## No file there , just an epitech header example
##

CC = g++
src = $(shell find Sources/ -type f -name '*.cpp')

NAME = zappy_gui
OBJ = ${src:.cpp=.o}
deps = $(src:.cpp=.d)
SFML = -lsfml-graphics -lsfml-window -lsfml-system

CFLAGS = -MMD -MP -Wall -Wextra -I Includes -I ../circular_buffer/include ${SFML} -g3 --std=c++20
CIRC_BUFF = -L../circular_buffer -lcirc_buff

.cpp.o:
	${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

${NAME}: ${OBJ}
	make re -C ../circular_buffer/
	${CC} -o ${NAME} ${OBJ} ${CFLAGS} ${CIRC_BUFF}

all : ${NAME}

clean :
	rm -rf ${OBJ}
	rm -rf ${deps}

-include $(deps)

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY: re tests_run fclean clean all
