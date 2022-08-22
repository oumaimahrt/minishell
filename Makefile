# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 09:56:57 by ohrete            #+#    #+#              #
#    Updated: 2022/08/22 11:14:03 by ohrete           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = minishell.c \
	expanding.c \
	tokenizer.c \
	token_utils.c \
	token_utils2.c \
	parser.c \
	execute_minishell.c \
	#./parsing/parse.c 

OBJS = $(SRCS:%.c=%.o)
LFLAGS = -lreadline -L/Users/ohrete/.brew/opt/readline/lib -I/Users/ohrete/.brew/opt/readline/include
CFLAGS = -fsanitize=address -g #-Wall -Wextra -Werror -fsanitize=address -g
LIBFT = ./libft/libft.a

all: $(NAME)
	
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $(NAME) 

$(LIBFT) :
	cd ./libft && make

clean :
	rm -f $(OBJS)
	cd ./libft && make clean

fclean : clean
	rm -f $(NAME)
	cd ./libft && make fclean

re: fclean all