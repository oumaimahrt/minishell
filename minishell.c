/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:26:50 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/11 22:39:07 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env *fst_link;
	//char *line;
	// int		i;

	// i = 0;
	fst_link = NULL;
    if (!ac || !av)
		return (0);
	// while (env[i])
	// {
	// 	printf("%s %d\n", env[i], i);
	// 	i++;
	// }
	expansion_env(&fst_link, env);
	while (fst_link)
	{
		printf("name = %s\n value = %s\n", fst_link->name, fst_link->value);
		fst_link = fst_link->next;
	}
	// while (1)
	// {
	// 	line = readline("minishell~ ");
	// 	if (line[0] != '\0')
	// 	{
	// 		add_history(line);
	// 		// tokenizer(env); //parsing
	// 	}
	// 	// if (!line)
	// 	// {
	// 	// 	printf("exit");
	// 	// 	exit(0);
	// 	// }
	// 	free(line);
	// 	//execution;
	// }
}