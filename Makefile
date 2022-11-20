NAME	= ft_containers
CC		= c++ -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
RM		= rm -rf

#VECTOR_FILES = tester/tester_vector
#STACK_FILES  = tester/tester_stack

FILES	=  $(VECTOR_FILES) $(STACK_FILES) main tester/tester_stack tester/tester_vector

SRC		= $(FILES:=.cpp)
OBJ		= $(FILES:=.o)

utility	= utility/ft_is_integral.hpp utility/ft_enable_if.hpp utility/ft_iterator.hpp \
		  utility/ft_lexicographical_compare.hpp utility/ft_iterator_traits.hpp utility/ft_pair.hpp 

vector  =  ft_vector/ft_vector.hpp 

stack   =  ft_stack/ft_stack.hpp

RDT	    =  RED_BLACK_Tree/BST.hpp RED_BLACK_Tree/RDT.hpp

MAP     = ft_map/ft_map.hpp

INCLUDES = $(utility) $(vector) $(stack) $(RDT)  $(MAP) tester/tester.hpp

GRAY 	= \e[33;2;37m
YELLOW	= \e[93;5;226m
GREEN 	= \033[1;32m
END		= \e[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDES)
	@$(CC)  $(OBJ) -o $(NAME)
	@printf " $(GREEN) - SUCCESS [ ✅ ] $(END)\n"

%.o: %.cpp $(INCLUDES)	
	@printf " $(GRAY)   - Compiling $< ⏳ ... $(END)"
	@$(CC) -c $< -o $@
	@printf " $(GRAY) [ ✅ ] $(END)\n"

clean:
	@printf " $(YELLOW) - OBJ FILES REMOVED [ ✅ ] $(END)\n"
	@$(RM) $(OBJ)

fclean: clean
	@printf " $(YELLOW) - EXECUTABLE REMOVED [ ✅ ] $(END)\n"
	@$(RM) $(NAME)

re: fclean all