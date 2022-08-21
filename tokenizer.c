/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:00:09 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/21 21:57:30 by ohrete           ###   ########.fr       */
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
		printf("ERROR: inclosed quotes\n");   //error in case of unclosed quotes
		return ;
	}
	add_token_last(head, new_node(ft_substr(line, index + 1, *i - index - 1), SQ));
	(*i)++;
}

void	double_quote(t_env *env, t_token **temp, char *line, int *i, char **av)
{
	int		index;
	char	*str;
	char	*expand;

	printf("FROM DQ %s\n", line);
	index = *i;
	(*i)++;
	while (line[*i] && line[*i] != '\"')
		(*i)++;
	if (!line[*i])
	{
		printf("ERROR: inclosed quotes\n");   //error in case of unclosed quotes
		return ;
	}
	// add_token_last(head, new_node(ft_substr(line, index + 1, *i - index - 1), DQ));
	printf("before \n");
	str = ft_substr(line, index + 1, *i - index - 1);
	printf("ana hnaaaa\n");
	expand = ft_expand(str, env, av);
	printf("after \n");
	//printf("str === %s\n", str);
	add_token_last(temp, new_node(expand, DQ));
	printf("00000\n");
	(*i)++;
}

void	setting_word(t_token *head, t_token **temp, char *line, int *i)
{
	int		index;
	char	*str;
	char	*expand;

	index = *i;
	while(line[*i] && skip_char(line[*i]))
		(*i)++;
	str = ft_substr(line, index , *i - index);
	//expand = ft_expand(str, head);
	//printf("expand = %s\n", expand);
	add_token_last(temp, new_node(str, 0));
	//(*i)++;
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
		add_token_last(head, new_node("<<", HERE_DOC));
		(*i)++;
	}
	else if (str[*i] == '>')
		add_token_last(head, new_node(">", OUTPUT));
	else if (str[*i] == '<')
		add_token_last(head, new_node("<", INPUT));
	(*i)++;
}

void	dollar(t_token *head, t_token **temp, char *line, int *i)
{
	int		index;
	char	*str;
	char	*expand;

	index = *i;
	(*i)++;
	while (line[*i] && other_char(line[*i]))
		(*i)++;
	str = ft_substr(line, index , *i - index);
	//expand = ft_expand(str, env, av);
	add_token_last(temp, new_node(expand, EXPAND));
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
    
	temp = head;
	i = 0;
	while (line [i])
	{
		if (line[i] == '\'')
		{
			printf("SINGLE Q\n");
			single_quote(temp, line, &i);
		}
		else if (line[i] == '\"')
		{
			printf("DOUBLE Q\n");
			double_quote(env, temp, line, &i, av);
		}
		// else if(space(line[i]))
		// 	i++;
		// else if (line[i] == '$')
		// {
		// 	printf("DOLLAR\n");
		// 	dollar(*head, temp, line, &i);
		// }
		// else if (line[i] == '<' || line[i] == '>')
		// {
		// 	printf("RED\n");
		// 	redirection(temp, line, &i);
		// }
		// else if (line[i] == '|')
		// 	pipe_sign(temp, &i);
		// else
		// {
		// 	printf("WORD\n");
		// 	setting_word(*head, temp, line, &i);
		// }
		//else
		    //i++;
	}
}
