NAME	= ft_containers
CC		= c++ -Wall -Wextra -Werror -std=c++98 -g
RM		= rm -rf

FILES	=  ft_vector/ft_vector

SRC		= $(FILES:=.cpp)
OBJ		= $(FILES:=.o)

utility	= utility/ft_is_integral.hpp utility/ft_enable_if.hpp utility/ft_iterator.hpp \
		  utility/ft_lexicographical_compare.hpp utility/ft_iterator_traits.hpp utility/ft_pair.hpp 

vector  =  ft_vector/ft_vector.hpp

stack   =  ft_stack/ft_stack.hpp

INCLUDES = $(utils) $(vector) $(stack)


GREEN 	= \x1b[42m
END		= \e[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDES)
	@$(CC)  $(OBJ) -o $(NAME)
	@printf " $(GREEN) SUCCESS $(END)\n"

%.o: %.cpp $(INCLUDES)
	@$(CC) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all