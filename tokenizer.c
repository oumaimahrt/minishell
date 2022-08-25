/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:00:09 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/25 20:36:05 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exemple: int x = 1;
// A lexer or tokeniser will split that up into tokens:
// for EX: 'int', 'x', '=', '1', ';'.
// A parser will take those tokens and use them 
// to understand in some way: we have a statement
// it's a definition of an integer
// the integer is called 'x'
// 'x' should be initialised with the value 1

// int ft_strchr_index(char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == (unsigned char)c)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

void	pipe_sign(t_token **head, int *i)
{
	add_token_last(head, new_node("|", PIPE));
	(*i)++;
}

// void	tokenizer(char *line, t_token **head, char **av, t_env *env)
// {
// 	int		i;
// 	t_token	**temp;
// 	t_save	*save;

// 	save = (t_save *)malloc(sizeof(t_save));
// 	save->av = av;
// 	save->env = env;
// 	temp = head;
// 	i = 0;
// 	while (line [i])
// 	{
// 		if (line[i] == '\'')
// 			single_quote(temp, line, &i);
// 		else if (line[i] == '\"')
// 			double_quote(save, temp, line, &i);
// 		else if (space(line[i]))
// 			i++;
// 		else if (line[i] == '$')
// 			dollar(save, temp, line, &i);
// 		else if (line[i] == '<' || line[i] == '>')
// 			redirection(temp, line, &i);
// 		else if (line[i] == '|')
// 			pipe_sign(temp, &i);
// 		else
// 			setting_word(save, temp, line, &i);
// 	}
// }

void	tokens(char *line, t_token **temp, t_save *save, int *i)
{
	if (line[*i] == '\'')
		single_quote(temp, line, i);
	else if (line[*i] == '\"')
		double_quote(save, temp, line, i);
	else if (space(line[*i]))
		(*i)++;
	else if (line[*i] == '$')
		dollar(save, temp, line, i);
	else if (line[*i] == '<' || line[*i] == '>')
		redirection(temp, line, i);
	else if (line[*i] == '|')
		pipe_sign(temp, i);
	else
		setting_word(save, temp, line, i);
	if (line[*i] == '\0')
		return;
}

void	tokenizer(char *line, t_token **head, char **av, t_env *env)
{
	int		i;
	t_token	**temp;
	t_save	*save;

	save = (t_save *)malloc(sizeof(t_save));
	save->av = av;
	save->env = env;
	temp = head;
	i = 0;
	while (line[i])
	{
		tokens(line, temp, save, &i);
		i++;
	}
}