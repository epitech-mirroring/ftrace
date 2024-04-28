##
## EPITECH PROJECT, 2024
## FTrace
## File description:
## This is the Makefile for the ftrace project
##

# All the source files
SOURCES			= 	src/ftrace.c \
					src/parse_cmd.c \
					src/execute_command.c \
					src/main_loop.c \
					src/print_help.c \
					src/print_syscall_info.c \
					src/follow_pid.c	\
					src/utils.c \
					src/map_function_adress.c

TESTS			=

# Compiler and linker settings
NAME 			= 	ftrace
CC				= 	gcc
FLAGS			= 	-W -Wall -Wextra --coverage -I./include -lelf
OBJS			= 	$(SOURCES:.c=.o)
TESTS_OBJS		= 	$(TESTS:.c=.o)
LOG				=	./build.log

.PHONY: $(NAME) all clean fclean re tests_run clean_test

# Colors and formatting
GREEN =		\033[1;32m
YELLOW =	\033[1;33m
RED =		\033[1;31m
BLUE =		\033[1;36m
GOLD =		\033[1;33m
MAGENTA =	\033[1;35m
RESET =		\033[0m

RUNNING = [$(YELLOW)~$(RESET)]
SUCCESS = [$(GREEN)✔$(RESET)]
FAILURE = [$(RED)✘$(RESET)]
SKIPPED = [$(MAGENTA)@$(RESET)]

all:		$(NAME)

$(NAME):	$(OBJS)
# Link the object files
		@printf "$(RUNNING) $(BLUE) 🔗  Linking$(RESET)"
		@$(CC) -o $(NAME) $(OBJS) $(FLAGS) \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
# Check if the binary was created
		@if [ -f $(NAME) ]; then \
			printf \
			"$(SUCCESS)$(GREEN)  🎉  $(NAME) built successfully$(RESET)\n";\
		else \
			printf "$(FAILURE)$(RED)  🚨  $(NAME) build failed$(RESET)\n"; \
			cat $(LOG); \
		fi

$(OBJS):	%.o: %.c
# Compile the source file
		@printf "$(RUNNING) $(BLUE) 🔨  $$(basename $<)$(RESET)"
		@$(CC) -o $@ -c $< $(FLAGS) \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

clean:
# Delete all the object files
		@for file in $(OBJS); do \
			printf "$(RUNNING) $(RED) 🗑️   Deleting $$file$(RESET)"; \
			if [ -f $$file ]; then \
				rm -f $$file >> $(LOG) 2>&1 \
				&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
			else \
				printf "\r$(SKIPPED)\n"; \
			fi; \
		done

fclean: clean clean_test
# Delete the binary
		@printf "$(RUNNING) $(RED) 🗑️   Deleting $(NAME)$(RESET)";
	    @if [ -f $(NAME) ]; then \
			rm -f $(NAME) >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		else \
			printf "\r$(SKIPPED)\n"; \
		fi
# Delete the log file
		@printf "$(RUNNING) $(RED) 🗑️   Deleting $(LOG)$(RESET)";
		@if [ -f $(LOG) ]; then \
			rm -f $(LOG) >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		else \
			printf "\r$(SKIPPED)\n"; \
		fi

re:			fclean all

$(TESTS_OBJS):	%.o: %.c
		@printf "$(RUNNING) $(BLUE) 🔨  $$(basename $<)$(RESET)"
		@$(CC) -o $@ -c $< $(FLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

tests_run: fclean $(OBJS) $(TESTS_OBJS)
	@printf "$(RUNNING) $(BLUE) 🔗  Linking$(RESET)"
	@$(CC) -o tests.out $(filter-out src/ftrace.o, $(OBJS)) \
	$(TESTS_OBJS) $(FLAGS) -lcriterion >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n";
	@printf "$(RUNNING)$(BLUE)  🧪  Running tests$(RESET)" \
	&& ./tests.out --xml=criterion.xml --ignore-warnings >> tests.log 2>&1 \
	&& printf "\r$(SUCCESS)\n" \
	|| printf "\r$(FAILURE)\n";
	@cat tests.log;
	@printf "$(RUNNING)$(YELLOW)  📊  Generating coverage$(RESET)" \
	&& gcovr --exclude tests/ >> coverage.log 2>&1 \
	&& printf "\r$(SUCCESS)\n" \
	|| printf "\r$(FAILURE)\n";
	@cat coverage.log;

clean_test:
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests.out$(RESET)"
	@if [ -f tests.out ]; then \
		rm -f tests.out >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️   Deleting coverage$(RESET)"
	@rm -f coverage* >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests/*.o$(RESET)"
	@rm -f $(TESTS_OBJS) >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting *.gcda$(RESET)"
	@find ./ -name "*.gcda" -delete >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting *.gcno$(RESET)"
	@find ./ -name "*.gcno" -delete >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting criterion.xml$(RESET)"
	@if [ -f criterion.xml ]; then \
		rm -f criterion.xml >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests.log$(RESET)"
	@if [ -f tests.log ]; then \
		rm -f tests.log >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@printf "$(RUNNING) $(RED) 🗑️   Deleting coverage.log$(RESET)"
	@if [ -f coverage.log ]; then \
		rm -f coverage.log >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	else \
		printf "\r$(SKIPPED)\n"; \
	fi
	@if [ -d .cache/ ]; then \
		printf "$(RUNNING) $(RED) 🗑️   Deleting .cache/$(RESET)"; \
		rm -rf .cache >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	fi
	@if [ -d .local/ ]; then \
		printf "$(RUNNING) $(RED) 🗑️   Deleting .local/$(RESET)"; \
		rm -rf .local >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	fi
