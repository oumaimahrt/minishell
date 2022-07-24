/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:26:50 by ohrete            #+#    #+#             */
/*   Updated: 2022/07/22 11:26:51 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_counter(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return(i);
}

char	**line_reading(char **line)
{
	int		i;
	char	**str;

	str = malloc(sizeof(char *) * (line_counter(line) + 1));
	i = 0;
	while (line[i])
	{
		i++;
		str[i] = ft_strdup(line[i]);
	}
	str[i] = 0;
	return (str);
}

int main(int ac, char **av, char **line)
{
	char	*str;

    (void)ac;
    (void)av;
	g_var.line = line_reading(line);
	g_var.str = line_reading(line);
	while (1)
	{
		str = readline("minishell~ ");
		if (!str)
		{
			printf("exit");
			exit(0);
		}
		//add_history(str);
	}
}