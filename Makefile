# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 14:07:31 by anajmi            #+#    #+#              #
#    Updated: 2022/09/28 21:03:03 by ohrete           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra 

PARSE =	\
	./Parsing/syntax_error.c			\
	./Parsing/ft_environment.c			\
	./Parsing/environment_utils.c		\
	./Parsing/tokenizer.c				\
	./Parsing/token_utils.c				\
	./Parsing/token_utils2.c			\
	./Parsing/expanding.c				\
	./Parsing/parser.c					\
	./Parsing/pars_utils.c				\
	./Parsing/pars_utils2.c				\
	./Parsing/signals.c					\
	./Parsing/tools.c					\
 

EXEC = \
	./minishell.c							\
	./Execution/breaking.c					\
	./Execution/builtin.c					\
	./Execution/directory.c					\
	./Execution/echo.c						\
	./Execution/environment.c				\
	./Execution/execution.c					\
	./Execution/executor_tools.c			\
	./Execution/executor1.c					\
	./Execution/executor2.c					\
	./Execution/heredoc.c					\
	./Execution/iterate_files.c				\
	./Execution/iterate_heredoc.c			\
	./Execution/iterate_pipes.c				\
	./Execution/environment/export_env.c	\
	./Execution/environment/init.c			\
	./Execution/environment/show.c			\
	./Execution/environment/tools.c			\
	./Execution/environment/unset.c			\

SRCS = $(PARSE) $(EXEC)
CONTROL = @stty -echoctl
RE_PATH = ~/.brew/opt/readline
LFLAGS = -lreadline -L $(RE_PATH)/lib -I $(RE_PATH)/include
OBJ = $(SRCS:.c=.o)

#*******************************#
#			LIBFT				#
#*******************************#

LIBFT = ./Libft
ARLIB = $(LIBFT)/libft.a
ALLIBFT = make -C $(LIBFT)
CLEANLIBFT = make clean -C $(LIBFT)
FCLEANLIBFT = rm -f $(ARLIB)
RELIBFT = make re -C $(LIBFT)

#*******************************#
#			LIBFT PLUS			#
#*******************************#

LIBPL = ./LibftPlus
ARPLS = $(LIBPL)/libftplus.a
ALLIBPL = make -C $(LIBPL)
CLEANLIBPL = make clean -C $(LIBPL)
FCLEANLIBPL = rm -f $(ARPLS)
RELIBPL = make re -C $(LIBPL)

#*******************************#
#			COLORS				#
#*******************************#

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

#*******************************#
#			EXECUTION			#
#*******************************#

.PHONY : all clean fclean re

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	$(ALLIBFT)
	$(ALLIBPL)
	$(CONTROL)
	gcc $(CFLAGS) $(OBJ) $(ARLIB) $(ARPLS) $(LFLAGS) -o $(NAME)
	@echo "$(C_GREEN)[MINISHELL MANDATORY CREATED!]$(C_RES)"

clean :
	@$(CLEANLIBFT)
	@$(CLEANLIBPL)
	rm -f $(OBJ)
	@echo "$(C_RED)[MINISHELL OBJECTS DELETED!]$(C_RES)"

fclean : clean
	@$(FCLEANLIBFT)
	@echo "$(C_RED)[LIBFT ARCHIVE DELETED!]$(C_RES)"
	@$(FCLEANLIBPL)
	@echo "$(C_RED)[LIBFT PLUS ARCHIVE DELETED!]$(C_RES)"
	@rm -f $(NAME)
	@echo "$(C_RED)[MINISHELL EXECUTABLES DELETED!]$(C_RES)"

re : fclean all

