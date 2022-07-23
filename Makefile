# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 09:56:57 by ohrete            #+#    #+#              #
#    Updated: 2022/07/22 22:10:19 by ohrete           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = minishell.c \
	execute_minishell.c \
	./parsing/parse.c 

OBJS = $(SRCS:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a

all: $(NAME)
	
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) 

$(LIBFT) :
	cd ./libft && make

clean :
	rm -f $(OBJS)
	cd ./libft && make clean

fclean : clean
	rm -f $(NAME)
	cd ./libft && make fclean

re: fclean all