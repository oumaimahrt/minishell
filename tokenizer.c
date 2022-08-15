/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:00:09 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/15 01:57:59 by ohrete           ###   ########.fr       */
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

int whitespace(char c)
{
    if ((c >= 9 && c >= 13) || c == 32)
        return (1);
    return (0);
}

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

t_token   *new_node(char *str, int id)
{
    t_token *new;
    
    new = malloc(sizeof(t_token));
    new->str = str;
    new->id = id;
    new->next = NULL;
    return (new);
}
void add_token_last(t_token **head, t_token *new)
{
    t_token *last;
    
    last = (*head);
    if (!(*head))
        (*head) = new;
    else
    {
        while (last->next)
            last = last->next;
        last->next = new;
    }
}

void single_quote(t_token **head, char *line, int *i)
{
    int index;

    index = *i;
    (*i)++;
    while (line[*i] && line[*i] != '\'')
        (*i)++;
    if (!line[*i] || (line[*i] && line[*i] != '\''))
    {
        printf("ERROR: inclosed quotes\n");   //error in case of unclosed quotes
        return ;
    }
    add_token_last(head, new_node(ft_substr(line, index + 1, *i - index - 1), SQ));
    (*i)++;
}

// void    double_quote(t_token **head, char *str, int *i)
// {
//     int index;

//     index = *i;
//     (*i)++;
//     while (str[*i] && str[i] != '\"')
//     {
//         if (str[*i])
//     }
// }

int skip_char(char c)
{
    if (c =='`' || c == '$' || c == '&' || c == '(' || c == ')' || c == ';'
            || c == '!' || c == '\'' || c == '\"' || c == '<' || c == '>' 
            || c == ' ' || c == '\t' || c == '|')
        return (0);
    return (1);
}

void    setting_word(t_token **head, char *str, int *i)
{
    int index;

    index = *i;
    while(str[*i] && skip_char(str[*i]))
        (*i)++;
    add_token_last(head, new_node(ft_substr(str, 0, *i - index + 1), 0));
    //printf("word2: %s\n", str);
}

void    redirection(t_token **head, char *str, int *i)
{
    if (str[*i] == '>')
        add_token_last(head, new_node(">", OUTPUT));
    else if (str[*i] == '<')
        add_token_last(head, new_node("<", INPUT));
    else if (str[*i] == '>' && str[*i + 1] == '>')
        add_token_last(head, new_node(">>", APPEND));
    else if (str[*i] == '<' && str[*i + 1] == '<')
        add_token_last(head, new_node("<<", HERE_DOC));
} 
void pipe_sign(t_token **head, int *i)
{
    add_token_last(head, new_node("|", PIPE));
    (*i)++;
}

void token(char *line, t_token **head)
{
    int i;
    t_token *word;
    
    word =  NULL;
    i = 0;
    while (line [i])
    {
        if (line[i] == '\'')
            single_quote(head, line, &i);
        // else if (line[i] == '\"')
        //     return (double_quote());
        // else if (line[i] == '$')
        //     return (dollar()); it gonna be handled in func of double quote & also in setting_word function
        else if (whitespace(line[i]))
            i++;
        if (line[i] == '<' || line[i] == '>')
            redirection(head, line, &i);
        else if (line[i] == '|')
            return (pipe_sign(head, &i));
        // else if (special_char(line[i]));
        //     return (NULL);
        else
            setting_word(head, line, &i);
        //printf("%d\n", i);
    }
}