SRC = initiate.c main.c time.c utils.c
NAME = philo
CC = gcc
FLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(OBJ)

re: fclean all

