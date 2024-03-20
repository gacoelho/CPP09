NAME =  PmergeMe

SRC		=  main.cpp PmergeMe.cpp

CC 		= c++

FLAGS	= -Wall -Wextra -Werror -std=c++98

OBJS 	= $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME) $(OBJS)

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
