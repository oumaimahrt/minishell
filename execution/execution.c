/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:25:54 by ohrete            #+#    #+#             */
/*   Updated: 2022/07/22 11:42:09 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

SRC = minishell.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) 


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all