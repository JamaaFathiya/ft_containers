NAME	= ft_containers
CC		= c++ -Wall -Wextra -Werror -std=c++98 -g
RM		= rm -rf

FILES	= ft_vector

SRC		= $(FILES:=.cpp)
OBJ		= $(FILES:=.o)

INCLUDES	= ft_vector.hpp ft_iterator.hpp ft_iterator_traits.hpp

GREEN 	= \x1b[42m
END		= \e[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDES)
	@$(CC) $(OBJ) -o $(NAME)
	@printf " $(GREEN) SUCCESS $(END)\n"

%.o: %.cpp $(INCLUDES)
	@$(CC) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all