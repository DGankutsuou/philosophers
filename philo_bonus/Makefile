CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRC = philo_utils.c philo.c main.c watcher.c

NAME = philo

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@echo nothing to be cleaned

fclean:
	rm -f $(NAME)

re: fclean all

easy: re
	make clean
	clear

easier: all clean
	clear
