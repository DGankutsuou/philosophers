CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = philo_utils.c philo.c main.c

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
