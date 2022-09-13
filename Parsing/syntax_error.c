/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 21:12:38 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/13 03:05:11 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(char *str)  // still empty node
{
	int	i;

	i = 0;
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (0);
	while (str[i] !='\0')
	{
		if((str[i] == '|' && str[i + 1] == '|'))
			return (0);
		i++;
	}
	if ((str[ft_strlen(str) - 1] == '|') || (str[ft_strlen(str) - 1] == '<') || (str[ft_strlen(str) - 1] == '>'))
		return (0);
	return (1);
}

// int syntax_error(char *str)  // still this case: > | l && empty node
// {
//     int i;

//     i = 0;
//     if (str[0] == '|')
//         return (0);
//     while (str[i] !='\0')
//     {
//         if(str[i] == '|' && str[i + 1] == '|')
//             return (0);
//         i++;
//     }
//     if (str[ft_strlen(str) - 1] == '|')
//         return (0);
//     return (1);
// }

// still case of begin with one pipe