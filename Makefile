
# ************************************************************************** #  
#                                                                            # 
#                                                        :::      ::::::::   # 
#   Makefile	                                        :+:      :+:    :+:  # 
#                                                    +:+ +:+         +:+     # 
#   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        # 
#                                                +#+#+#+#+#+   +#+           # 
#   Created: 2022/12/18 12:34:45 by shovsepy          #+#    #+#             # 
#   Updated: 2022/12/18 12:36:09 by shovsepy         ###   ########.fr       #  
#                                                                            # 
# ************************************************************************** # 

NAME = ircserv

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDES = -I ./includes

RM = rm -rf


.cpp.o:
	@echo "\n"
	@echo "\033[0;32mCompiling IRC server..."
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $(<:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n"
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "\033[0;32m"

clean:
	@echo "\033[0;31mRemoving binaries..."
	@$(RM) $(OBJS)
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	@$(RM) $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: all clean, fclean, re
