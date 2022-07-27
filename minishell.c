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

int main(int ac, char **av)
{
	char	*line;

    (void)ac;
    (void)av;
	while (1)
	{
		line = readline("minishell~ ");
		if (line[0] != '\0')
		{
			//parsing
			add_history(line);
		}
		// if (!line )
		// {
		// 	//printf("exit");
		// 	exit(0);
		// }
		free(line);
		//execution;
	}
}