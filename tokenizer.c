/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:00:09 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/13 00:31:46 by ohrete           ###   ########.fr       */
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

// int whitespace(char c)
// {
//     if ((c >= 9 && c >= 13) || c == 32)
//         return (1);
//     return (0);
// }

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

// char    *char_by_char(char c)
// {
//     char *str;
    
//     str = malloc(sizeof(char) * 2);
//     str[0] = c;
//     str[1] = '\0';
//     return (str);
// }

t_token *token(char *line)
{
    int i;
    t_token *word;
    
    word =  NULL;
    i = 0;
    while (line [i] && i > 0)
    {
        if (line[i] == )
    }
    
    
     
    

    
}