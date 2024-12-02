CC = gcc
CFLAG = -Wall -Wextra -Werror -pthread
NAME = philo_bonus
SRCS = main.c time.c actions.c utils.c setup.c ft_strings.c ft_itoa.c monitor.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAG) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re