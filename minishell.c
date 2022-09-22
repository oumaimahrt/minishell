/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:15:08 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/22 23:42:55 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_vars	*var;
	t_token	*data;
	t_env	*fst_link;
	t_final *final_data;
	char	*line;
	
	int id ;
	id = 1;
	if (ac > 1)
		return (0);
	var = malloc(sizeof(t_vars));
	initialisation(var, env);
	fst_link = setting_env(env);
	fst_link->env_var = var;
	ft_signals();
	while (1)
	{
		line = readline("minishell→ ");
		ft_signals();
		if (!line) 
		{
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		if (line[0] != '\0')
		{
			if (syntax_error(line) != 0)
			{
				add_history(line);
				data = tokenizer(line, av, fst_link);
				// while (data != NULL)
				// {
				// 	printf("word1 = %s, id = %d\n", data->str, data->id);
				// 	data = data->next;
				// }
				final_data = ft_parser(data);
				executor(var, &final_data);
				// parser (&data);
				// // // printf("output %s\n", data->str);
				//@ft_output(final_data);
				//*printf("data ===== %s\n", data->str);
				free_tokens(data); //holaaa
				// ft_freeparser(final_data);
				free(line);
				// system("leaks minishell");
				// }
			}
			else
				ft_putstr_fd("minishell: syntax error\n", 2);
		}
	}
}