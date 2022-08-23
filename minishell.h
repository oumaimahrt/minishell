/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:11:06 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/23 23:32:55 by ohrete           ###   ########.fr       */
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
# define WORD 'W'
int g_status;
//env
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

//tokenizer
typedef struct s_token
{
	char			*str;
	int				id;
	char			**av;
	t_env			*fst_link;
	struct s_token	*next;
}	t_token;

//save last value of envp and argv
typedef struct s_save
{
	t_env *env;
	char **av;
}	t_save;
//parser
// typedef struct s_cmd
// {
//     char            *name;
//     struct s_cmd    *next;
// }   t_cmd;

// typedef struct s_redir
// {
//     char            *str;
//     int             id;
//     struct s_redir  *next;
// }   t_redir;

// typedef struct s_line
// {
// 	t_token			*head;
// 	struct s_line	*next;
// }	t_line;

char	*search_name(char *name, int i);
char	*search_value(char *value, int i);
char	tokenizer(char **env);
t_env	*fill_struct(char *name, char *value);
void	add_first(t_env **fst_link, t_env *new);
void	add_last(t_env **head, t_env *new);
char	*getting_env(t_env *env, char *name);
t_env	*setting_env(char **env);
int		space(char c);
t_token	*new_node(char *str, int id);
void	add_token_last(t_token **head, t_token *new);
void	single_quote(t_token **head, char *line, int *i);
char	*ft_expand(char *str, t_env *env, char **av);
void	double_quote(t_save *save, t_token **temp, char *line, int *i);
int		skip_char(char c);
void	setting_word(t_save *save, t_token **temp, char *line, int *i);
void	redirection(t_token **head, char *str, int *i);
int		other_char(char c);
void	dollar(t_save *save, t_token **temp, char *line, int *i);
void	pipe_sign(t_token **head, int *i);
void	token(char *line, t_token **head, char **av, t_env *env);
void	ft_signals(void);
void	rl_replace_line (const char *text, int clear_undo);

#endif
