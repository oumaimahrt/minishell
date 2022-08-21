/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:00:09 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/21 16:50:49 by ohrete           ###   ########.fr       */
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



// int special_char(char c)
// {
//     if (c == '<')
//         return (INPUT);
//     if (c == '>')
//         return (OUTPUT);
//     if (c == '|')
//         return (PIPE);
//     if (c == '$')
//         return (DOLLAR);
//     if (c == '\'')
//         return (SQ);
//     if (c == '\"')
//         return (DQ);
//     return (0);
// }

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



// void    space(t_token **head, char *str, int *i)
// {
//     int index;
    
//     index = *i;
//     while (str[*i] == ' ')
//         (*i)++;
//     add_token_last(head, new_node(" ", SPACE));
//}

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

// void expand_value(t_token **head, t_env *env)
// {
//     char *str;
//     t_token *temp;
    
//     temp = *head;
//     while (temp)
//     {
//         if (temp->id)
//         {
//             if (!ft_strcmp(temp->content, "?"))
//             {
//                 free(temp->content);
//                 temp->content =ft_strdup("$?");
//             }
//             else
//             {
//                 str = ft_strdup(temp->content);
//                 free(temp->content);
//                 temp->content = ft_strdup(getting_env(env, str));
//                 free(str);
//             }
//         }
//         temp = temp->next;
//     }
// }

// char *expand_dollar(char *str, t_env *env)
// {
//     int i;
//     char *res;
//     t_token *head;
//     t_token *temp;

//     i = 0;
//     head = NULL;
//     res = NULL;
//     if (!str)
//         return (NULL);
//     while (str[i])
//         expand_value(&head, env);
//     temp = head;
//     while (temp)
//     {
//         res = ft_strjoin(res, temp->content);
//         temp = temp->next;
//     }
//     free(str);
//     //ft_lstclear(&head);
//     return (res);
    
// }


void	double_quote(t_token *head, t_token **temp, char *line, int *i)
{
	int		index;
	char	*str;
	char	*expand;
	// t_env *env;

	// env = NULL;
	index = *i;
	(*i)++;
	//printf("hahahahahhah\n");
	while (line[*i] && line[*i] != '\"')
		(*i)++;
	if (!line[*i])
	{
		printf("ERROR: inclosed quotes\n");   //error in case of unclosed quotes
		return ;
	}
	// add_token_last(head, new_node(ft_substr(line, index + 1, *i - index - 1), DQ));
	str = ft_substr(line, index + 1, *i - index - 1);
	expand = ft_expand(str, head);
	//printf("str === %s\n", str);
	add_token_last(temp, new_node(expand, DQ));
	(*i)++;
}



void	setting_word(t_token **head, char *str, int *i)
{
	int	index;

	index = *i;
	while(str[*i] && skip_char(str[*i]))
		(*i)++;
	add_token_last(head, new_node(ft_substr(str, index , *i - index), 0));
	
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

void	dollar(t_token **head, char *str, int *i)
{
	int	index;

	index = *i;
	(*i)++;
	while (str[*i] && other_char(str[*i]))
	{
		//printf("INSIDE\n");
		(*i)++;
	}
	add_token_last(head, new_node(ft_substr(str, index , *i - index), EXPAND));
	// (*i)++;
	//printf("00 %c\n", str[*i]);
	//printf("%s", (*head)->str);
}

void	pipe_sign(t_token **head, int *i)
{
	add_token_last(head, new_node("|", PIPE));
	(*i)++;
}

void	token(char *line, t_token **head)
{
	int		i;
	t_token	**temp;
    
	temp = head;
	i = 0;
	while (line [i])
	{
		//printf("kakakakakak\n");
		if (line[i] == '\'')
			single_quote(temp, line, &i);
		else if (line[i] == '\"')
			double_quote(*head, temp, line, &i); //handle expansion inside it
		//printf("22222kakakakakak\n");
		else if(space(line[i]))
			i++;
		// else if (line[i] == ' ')
		//     space(head, line, &i);
		else if (line[i] == '$')
			dollar(temp, line, &i); //it's gonna be handled in func of double quote & also in setting_word function
		else if (line[i] == '<' || line[i] == '>')
			redirection(temp, line, &i); //to handle expand inside it, call func of double quote
		else if (line[i] == '|')
			pipe_sign(temp, &i);
		// else if (special_char(line[i]));
		//     return (NULL);
		else
			setting_word(temp, line, &i);  //expanding the key
		// else
		//     i++;
	}
}
