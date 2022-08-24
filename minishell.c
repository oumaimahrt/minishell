/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:26:50 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/24 20:29:10 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_c(int sig)
{
	(void)sig;

	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}
void	ft_signals(void)
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_token	*data;
	char	*line;
	t_env	*fst_link;
	// int		i;

	// i = 0;
	// data->head = NULL;
	// data->fst_link = NULL;
	//(void)ac;
	if (ac > 1)
		return (0);
	// while (env[i])
	// {
	// 	printf("%s %d\n", env[i], i);
	// 	i++;
	// }
	//data = (t_token *)malloc(sizeof(t_token));
	//data->av = av;
	//printf("********%s\n", data->av[0]);
	fst_link = setting_env(env);
	// while (data->fst_link)
	// {
	// 	printf("%s==%s\n", data->fst_link->name, data->fst_link->value);
	// 	data->fst_link = data->fst_link->next;
	// }
	while (1)
	{
		ft_signals();
		line = readline("minishell~ ");
		if (!line) 
		{
			printf("minishell~ exit");
			exit(0); //control_D
		}
		if (line[0] != '\0') //for skipping \n
		{
			add_history(line);
			token(line, &data, av, fst_link);
			while (data)
			{
				printf("word1 = %s, id = %d\n", data->str, data->id);
				data = data->next;
			}
			//execution;
			free(line);
			//system("leaks minishell");
		}
	}
}