/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:00:09 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/23 17:06:48 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exemple: int x = 1;
// A lexer or tokeniser will split that up into tokens 'int', 'x', '=', '1', ';'.
// A parser will take those tokens and use them to understand in some way:
// we have a statement
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


void	single_quote(t_token **head, char *line, int *i)
{
	int	index;

	index = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (!line[*i])
	{
		printf("ERROR: inclosed quotes\n");
		return ;
	}
	add_token_last(head, new_node(ft_substr(line, index + 1, *i - index - 1), SQ));
	(*i)++;
}

void	double_quote(t_save *save, t_token **temp, char *line, int *i)
{
	int		index;
	char	*str;
	char	*expand;

	index = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\"')
		(*i)++;
	if (!line[*i])
	{
		printf("ERROR: inclosed quotes\n");
		return ;
	}
	str = ft_substr(line, index + 1, *i - index - 1);
	expand = ft_expand(str, save->env, save->av);
	add_token_last(temp, new_node(expand, DQ));
	(*i)++;
}

void	setting_word(t_save *save, t_token **temp, char *line, int *i)
{
	int		index;
	char	*str;
	char	*expand;

	index = *i;
	while(line[*i] && skip_char(line[*i]))
		(*i)++;
	str = ft_substr(line, index , *i - index);
	expand = ft_expand(str, save->env, save->av);
	add_token_last(temp, new_node(expand, WORD));
}

void	redirection(t_token **head, char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		add_token_last(head, new_node(">>", APPEND));
		(*i)++;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		add_token_last(head, new_node("<<", HERE_DOC)); // don't expand it fixed
		(*i)++;
	}
	else if (str[*i] == '>')
		add_token_last(head, new_node(">", OUTPUT));
	else if (str[*i] == '<')
		add_token_last(head, new_node("<", INPUT));
	(*i)++;
}

void	dollar(t_save *save, t_token **temp, char *line, int *i)
{
	int		index;
	char	*str;
	char	*expand;
	t_token	*copy;

	copy = *temp;
	index = *i;
	(*i)++;
	while (line[*i] && other_char(line[*i]))
		(*i)++;
	str = ft_substr(line, index , *i - index);
	while(copy != NULL)
	{
		if (copy->next == NULL)
			break;
		copy = copy->next;
	}
	if (copy && ft_strcmp(copy->str, "<<") == 0)
		add_token_last(temp, new_node(str, EXPAND));
	else
	{
		expand = ft_expand(str, save->env, save->av);
		add_token_last(temp, new_node(expand, EXPAND));
	}
}

void	pipe_sign(t_token **head, int *i)
{
	add_token_last(head, new_node("|", PIPE));
	(*i)++;
}

void	token(char *line, t_token **head, char **av, t_env *env)
{
	int		i;
	t_token	**temp;
    t_save	*save;

	save = (t_save *)malloc(sizeof(t_save));
	save->av = av;
	save->env = env;
	temp = head;
	i = 0;
	while (line [i])
	{
		if (line[i] == '\'')
			single_quote(temp, line, &i);
		else if (line[i] == '\"')
			double_quote(save, temp, line, &i);
		else if(space(line[i]))
			i++;
		else if (line[i] == '$')
			dollar(save, temp, line, &i);
		else if (line[i] == '<' || line[i] == '>')
			redirection(temp, line, &i);
		else if (line[i] == '|')
			pipe_sign(temp, &i);
		else
			setting_word(save, temp, line, &i);
	}
}
