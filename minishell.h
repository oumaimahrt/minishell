/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:11:06 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/14 23:44:10 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# define OUTPUT '>'
# define INPUT '<'
# define PIPE '|'
# define APPEND 'A' // >>
# define EXPAND '$'
# define SQ '\''
# define DQ '\"'
# define HERE_DOC 'H' // <<


//env
typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}   t_env;

//tokenizer
typedef struct s_token
{
    char            *str;
    int             id;
    struct s_token  *next;
}   t_token;

//parser
typedef struct s_cmd
{
    char            *name;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_redir
{
    char            *str;
    int             id;
    struct s_redir  *next;
}   t_redir;

typedef struct  s_line
{
    t_cmd           *cmd;
    t_redir         *redir;
    t_token         *head;
    t_env           *fst_link;
    struct s_line   *next;
}   t_line;


char	tokenizer(char **env);
//char	**copy_env(char **env);
void add_last(t_env **head, t_env *new);
t_env   *fill_struct(char *name, char *value);
void    expansion_env(t_env **fst_link, char **env);
void token(char *line, t_token **head);

#endif
