/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:25:58 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/22 21:11:54 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*single_quote(t_token **head, char *line, int *i)
{
	char 	*value;
	int	index;

	index = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (!line[*i])
	{
		ft_putstr_fd("ERROR: inclosed single quotes\n", 2);
	}
	value = ft_substr(line, index + 1, *i - index - 1);
	(*i)++;
	return (value);
}

char	*double_quote(t_save *save, t_token **temp, char *line, int *i)
{
	int		index;
	char	*expand;
	char	*value;

	index = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\"')
		(*i)++;
	if (!line[*i]) 
		ft_putstr_fd("ERROR: inclosed double quotes\n", 2);
	value = ft_substr(line, index + 1, *i - index - 1);
	if (check_dollar(value) != 0)
	{
		expand = value;
		value = ft_expand(value, save->env, save->av);
		free (expand);
	}
	(*i)++;
	return (value);
}

char	*dollar(t_save *save, t_token **temp, char *line, int *i)
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
	str = ft_substr(line, index, *i - index);
	while (copy != NULL)
	{
		if (copy && ft_strcmp(copy->str, "<<") == 0)
		{
			return (str);
		}
		else if (copy->next == NULL)
			break ;
		copy = copy->next;
	}
	expand = ft_expand(str, save->env, save->av);
	free(str);
	return (expand);
}

void	redirection(t_token **head, char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		add_token_last(head, new_node(ft_strdup(">>"), APPEND));
		(*i)++;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		add_token_last(head, new_node(ft_strdup("<<"), HERE_DOC));
		(*i)++;
	}
	else if (str[*i] == '>')
		add_token_last(head, new_node(ft_strdup(">"), OUTPUT));
	else if (str[*i] == '<')
		add_token_last(head, new_node(ft_strdup("<"), INPUT));
	(*i)++;
}

char	*convert_char_str(char c)
{
	char	*str;
	
	str = malloc (sizeof (char) * 2);
	if (!str)
	{
		ft_putstr_fd("error allocation\n", 2);
		return (NULL);
	}
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	setting_word(t_save *save, t_token **temp, char *line, int *i)
{
	char	*value;
	char	*str;
	char	*expand;

	value = malloc (sizeof (char));
	value[0] = '\0';
	while (line[*i] && skip_char(line[*i]))
	{
		if (line[*i] == '\'')
		{
			str = single_quote(temp, line, i);
			value = ft_strjoin (value, str);
		}
		else if (line[*i] == '\"')
		{
			str = double_quote(save, temp, line, i);
			value = ft_strjoin (value, str);
		}
		else
		{
			if (line[*i] == '$')
				value = ft_strjoin(value, dollar(save, temp, line, i));
			else
			{
				str = convert_char_str(line[*i]);
				value = ft_strjoin (value, str);
				(*i)++;
			}
		}
	}
	add_token_last(temp, new_node(value, WORD));
}
