/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:11:06 by ohrete            #+#    #+#             */
/*   Updated: 2022/07/22 22:15:16 by ohrete           ###   ########.fr       */
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

// typedef struct s_global
// {
//     char    **line;
//     char    **str;
// }   t_global;

// t_global    g_var;

// typedef struct s_words
// {
//     char *name;
//     int id;
//     t_words *next;
// }   t_words;

// typedef struct  s_gencmd
// {
//     struct *s_words;
//     t_gencmd *next; 
// }   t_gencmd;

typedef struct s_tokenization
{
    char    *line;
    char    c;
}   t_tokenization;


void	parsing(char *line);

#endif
