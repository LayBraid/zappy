##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Makefile
##

all:
	make -C gui/
	mv gui/zappy_gui .
	make -C server/
	mv server/zappy_server .
	make -C ai/


clean:
	make clean -C gui/
	make clean -C server/
	make clean -C ai/


fclean:
	make fclean -C gui/
	rm -f zappy_gui
	make fclean -C server/
	rm -f zappy_server
	rm -f zappy_ai

re:
	make re -C gui/
	mv gui/zappy_gui .
	make re -C server/
	mv server/zappy_server .
	make -C ai/
