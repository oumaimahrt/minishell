/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:26:50 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/21 16:05:36 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_token *data;
	char *line;
	// int		i;

	// i = 0;
	// data->head = NULL;
	// data->fst_link = NULL;
	(void)ac;
    // if (!ac || !av)
	// 	return (0);
	// while (env[i])
	// {
	// 	printf("%s %d\n", env[i], i);
	// 	i++;
	// }
	data = (t_token *)malloc(sizeof(t_token));
	data->av = av;
	//printf("********%s\n", data->av[0]);
	data->fst_link= setting_env(env);
	// while (data->fst_link)
	// {
	// 	printf("name = %s\n value = %s\n", data->fst_link->name, data->fst_link->value);
	// 	data->fst_link = data->fst_link->next;
	// }
	while (1)
	{
		line = readline("minishell~ ");
		if (line[0] != '\0')
		{
			add_history(line);
			token(line, &data);
			//printf("my expand\n");
			// while (data)
			// {
			// 	printf("word1 = %s, id = %d\n", data->str, data->id);
			// 	data = data->next;
			// }
			// parser(fst_link, line); //parsing
		}
		// if (!line)
		// {
		// 	printf("exit");
		// 	exit(0);
		// }
		free(line);
		//execution;
	}
}