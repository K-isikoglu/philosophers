.PHONY: all clean fclean re

NAME = philo
OBJECTS = $(SRCS:.c=.o)

SRCS := philo.c philo_utils.c routine.c routine_utils.c ft_atoi.c ft_think.c routine_funcs.c

all: $(NAME)

$(NAME): $(OBJECTS)
	@cc $(OBJECTS) -o $(NAME)

$(OBJECTS): $(SRCS)
	@cc -c $^ -Wall -Wextra -Werror

clean:
	@rm -f $(OBJECTS) $(BNSOBJECTS)

fclean: clean
	@rm -f $(NAME) $(BNSNAME)

re: fclean all
