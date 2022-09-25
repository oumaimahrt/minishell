/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/25 15:55:41 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		trouble("fork", NULL, "error", 1);
	return (pid);
}

void	fill_path(t_vars *var)
{
	t_allways	aws;

	ft_free(var->tmpp);
	var->tmpp = ft_split(get_env_var(var, "PATH"), ':');
	ft_free(var->exepath);
	var->exepath = malloc(sizeof(char *) * (ft_lstlen(var->tmpp) + 3));
	aws.i = 0;
	while (var->tmpp[aws.i])
	{
		var->exepath[aws.i] = ft_strjoin(var->tmpp[aws.i], "/");
		aws.i++;
	}
	var->exepath[aws.i] = ft_strdup("./");
	var->exepath[aws.i + 1] = ft_strdup("");
	var->exepath[aws.i + 2] = NULL;
}

char	*exe_path_set(t_vars *var, char *exe)
{
	t_allways	aws;

	if (check_env_var(var, "PATH"))
		trouble_exit(exe, NULL, "PATH not set", 1);
	fill_path(var);
	aws.i = 0;
	while (var->exepath[aws.i])
	{
		if (!access(ft_strjoin(var->exepath[aws.i], exe), F_OK))
			return (ft_strjoin(var->exepath[aws.i], exe));
		aws.i++;
	}
	return (NULL);
}

void	initialisation(t_vars *var, char **av, char **env)
{
	var->tmp = malloc(sizeof(char));
	var->tmp2 = malloc(sizeof(char));
	var->tmpp = malloc(sizeof(char *));
	var->tmpp[0] = NULL;
	var->main_name = ft_strdup(av[0]);
	var->exepath = malloc(sizeof(char *));
	var->exepath[0] = NULL;
	var->hdocs = malloc(sizeof(char));
	var->hdocs[0] = '\0';
	var->infile = -1;
	var->env.env = env;
	var->pid = malloc(sizeof(int) * FILENAME_MAX);
	if (!env)
	{
		var->env.env = malloc(sizeof(char *));
		var->env.env[0] = NULL;
		return ;
	}
	init_environment(var);
	init_export(var);
	var->tmp0 = ft_itoa(ft_atoi(get_env_var(var, "SHLVL")) + 1);
	var->tmp1 = ft_strjoin("SHLVL=", var->tmp0);
	ft_export(var, var->tmp1, 0);
	ft_unset(var, "OLDPWD");
	ft_export(var, "OLDPWD", 1);
}
