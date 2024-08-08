RED_TEXT =\033[1;31m
GREEN_TEXT =\033[1;32m
YELLOW_TEXT =\033[1;33m
RESET_TEXT =\033[0m

NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = cc
READLINE_DIR=$(shell brew --prefix readline)
EXECUTION_DIR = execution
SIGNALS_DIR = signals
PARSING_DIR = parsing

M_SOURCES = $(wildcard $(EXECUTION_DIR)/*.c $(PARSING_DIR)/*.c $(SIGNALS_DIR)/*.c)

M_OBJECTS = ${M_SOURCES:.c=.o}

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -I $(READLINE_DIR)/include -c $< -o $@

all : $(NAME)

$(NAME) : $(M_OBJECTS)
	@$(CC) $(CFLAGS) -L $(READLINE_DIR)/lib $(M_OBJECTS) -lreadline -o $(NAME)
	@echo "$(GREEN_TEXT)[the executable created successfully]$(RESET_TEXT)"

clean :
	@rm -rf $(M_OBJECTS)
	@echo "$(RED_TEXT)object files removed successfully$(RESET_TEXT)"
fclean : clean
	@rm -rf $(NAME)
	@echo "$(RED_TEXT)the executable files removed successfully$(RESET_TEXT)"

re : fclean all
.PHONY : clean
