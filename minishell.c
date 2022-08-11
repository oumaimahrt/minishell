/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:26:50 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/11 01:41:59 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**table;
	//char *line;
	// int		i;

	// i = 0;
    if (!ac || !av)
		return (0);
	// while (env[i])
	// {
	// 	printf("%s %d\n", env[i], i);
	// 	i++;
	// }
	table = copy_env(env);
	expansion_env(table);
// 	while (1)
// 	{
// 		line = readline("minishell~ ");
// 		if (line[0] != '\0')
// 		{
// 			add_history(line);
// 			// tokenizer(env); //parsing
// 		}
// 		// if (!line)
// 		// {
// 		// 	printf("exit");
// 		// 	exit(0);
// 		// }
// 		free(line);
// 		//execution;
// 	}
}