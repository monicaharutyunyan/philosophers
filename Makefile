NAME 		= philo

CC 			= cc

CFLAGS 		= -Wall -Wextra  #-Werror #-fsanitize=address -g -ggdb3  #-Werror#TODO add flags

SRCS		= $(wildcard *.c)

OBJS 		= $(SRCS:%.c=%.o)

%.c:
	@$(CC) $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅$(NAME) created!$(DEFAULT) 😊🥑"

clean:
	@rm -f ./*.o
	@echo "$(YELLOW)🧨 Object files deleted!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)💣 All deleted!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m

