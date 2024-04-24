##
## EPITECH PROJECT, 2024
## mirror_ftrace
## File description:
## Makefile
##

SRC 	= 	test.c

OBJ 	= 	$(SRC:.c=.o)

NAME 	= 	test_runner

CC 		= 	gcc

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ)
	@echo " 🔨 Compiled $(NAME)"

clean:
	@rm -f $(OBJ)
	@echo " 🗑️ Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo " 🗑️  cleaned bin"

re: fclean all
