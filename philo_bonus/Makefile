NAME = philo_bonus

CC = gcc
FL = -Wall -Wextra -Werror

SRCS =	philo.c utils.c processes.c activities.c life_check.c
OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FL) -o $@ -c $^

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re