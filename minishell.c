/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:15:08 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/28 18:39:56 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_vars	*var;
	t_token	*data;
	t_env	*fst_link;
	t_final *final_data;
	t_save	*save;

	int id ;
	id = 1;
	if (ac > 1)
		return (0);
	var = malloc(sizeof(t_vars));
	initialisation(var, av, env);
	fst_link = setting_env(env);
	fst_link->env_var = var;
	save = (t_save *)malloc(sizeof(t_save));
	save->av = av;
	save->env = fst_link;
	ft_signals();
	while (1)
	{
		var->line = readline("minishell→ ");
		ft_signals();
		if (!var->line) 
		{
			ft_putendl_fd("exit", 1);
			exit(0); //control_D
		}
		if (var->line[0] != '\0') //for skipping \n
		{
			add_history(var->line);
			if (syntax_error(var->line) == 1)
			{
				data = tokenizer(var->line, save);
				if (data && save->error == 0)
				{
					// while (data != NULL)
					// {
					// 	printf("word1 = %s, id = %d\n", data->str, data->id);
					// 	data = data->next;
					// }
					final_data = ft_parser(data);
					executor(var, &final_data);
					free_parser(final_data);
					//@ft_output(final_data);
				}
				free_tokens(data);
			}
			else
				trouble(NULL, NULL, "syntax error", 258);	
		}
		free(var->line);
	}
}

