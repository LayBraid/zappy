##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile for zappy_ai
##

SRC     =   src/zappy_ai

NAME	=   zappy_ai

all:	$(NAME)

$(NAME): ## Compile AI
	cp src/$(NAME) ../
	chmod a+x ../$(NAME)

clean: ## Clean AI
	@echo "Nothing to clean"

fclean: ## Force clean AI
	clean
	rm -f ../$(NAME)

re: ## Recompile AI
	fclean
	all

help: ## Display this help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: all clean fclean re
