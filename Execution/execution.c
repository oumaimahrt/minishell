/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:12:12 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/11 15:34:54 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*********************/
/* BUILTIN FUNCTIONS */
/*********************/

void	trouble(char *s)
{
	printf("trouble in %s.\n", s);
	exit(0);
}

int	fork1(void)
{
	int pid;

	pid = fork();
	if (pid == -1)
		trouble("fork");
	return pid;
}

char	*dir()
{
	char	cwd[FILENAME_MAX];

	getcwd(cwd, sizeof(cwd));
	return (ft_strdup(cwd));
}

int	echo_check(char *args)
{
	t_allways aws;

	aws.j = 1;
	while (args[aws.j])
	{
		if (args[aws.j] != 'n')
			return (0);
		aws.j++;
	}
	return (1);
}

int	echo(t_vars *var, t_final *final)
{
	t_allways aws;

	aws.i = 1;
	aws.k = 1;
	
	if (final->cmd[aws.i][0] == '-' && final->cmd[aws.i][1])
	{
		while (final->cmd[aws.i] && final->cmd[aws.i][0] == '-' && echo_check(final->cmd[aws.i]))
		{
			aws.k = 0;
			aws.i++;
		}
	}
	while (final->cmd[aws.i])
	{
		printf("%s ", final->cmd[aws.i]);
		aws.i++;
	}
	printf("\b");
	if (aws.k)
		printf("\n");
	return (1);
}

int	cd(t_vars *var, t_final *final)
{
	if (check_env_var(var, "HOME"))
	{
		if (ft_lstlen(final->cmd) == 1)
		{
			final->cmd[1] = ft_strdup(get_env_var(var, "HOME"));// SIGFAULT
			final->cmd[2] = NULL;
		}
	}
	else
		trouble("cd $HOME"); //bash: cd: HOME not set

	if (!ft_strcmp(final->cmd[1], "~"))
	{
		free(final->cmd[1]);
		final->cmd[1] = ft_strdup(var->tilda);
	}
	if (final->cmd[1][0] == '-')
	{
		printf("minishell: cd: %s: invalid option\n", final->cmd[0]);
		return (0);
	}
	else if (ft_lstlen(final->cmd) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (0);
	}
	else
	{
		free(var->tmp3);
		var->tmp3 = dir();
		if (chdir(final->cmd[1]))
		{
			printf("minishell: cd: %s: No such file or directory\n", final->cmd[1]);
			return (0);
		}
		ft_export(var, ft_strjoin("OLDPWD=", var->tmp3), 0);
		ft_export(var, ft_strjoin("PWD=", dir()), 0);
	}
	// else
	// 	trouble("cd $PWD");
	return (1);
}

int	pwd(t_vars *var)
{
	printf("%s\n", dir());
	return (1);
}

int	export(t_vars *var, t_final *final)
{
	t_allways aws;

	if (!final->cmd[1])
		show_exp(var);
	else
	{
		aws.i = 1;
		while (final->cmd[aws.i])
		{
			// if (ft_isalpha(ecmd->args[aws.i][0]) || ecmd->args[aws.i][0] == '_' || ecmd->args[aws.i][0] == '$')
				ft_export(var, final->cmd[aws.i], 0);
			// else
			// 	printf("bash: export: `%s': not a valid identifier\n", ecmd->args[aws.i]);
			aws.i++;
		}
	}
	return (1);
}

int	unset(t_vars *var, t_final *final)
{
	t_allways aws;

	aws.i = 1;
	while (final->cmd[aws.i])
	{
		ft_unset(var, final->cmd[aws.i]);
		aws.i++;
	}
	return (1);
}

int	environment(t_vars *var, t_final *final)
{
	if (!final->cmd[1])
		show_env(var); // update SHLVL=4
	else
		printf("env: ‘%s’: No such file or directory\n", final->cmd[1]);
	return (1);
}

static int	check_exit(char *cmds)
{
	int i, j;
	t_allways aws;

	aws.i = 0;
	if (cmds[aws.i] == '-' || cmds[aws.i] == '+')
		aws.i++;
	if (cmds[aws.i] == '\0')
		return (0);
	while (cmds[aws.i])
	{
		if (!ft_isdigit(cmds[aws.i]))
			return (0);
		aws.i++;
	}
	return (1);
}

int	exiting(t_vars *var, t_final *final)
{
	t_allways aws;

	aws.i = ft_lstlen(final->cmd);
	// unsigned char c = 656884651669684;
	// printf("%d\n", c);
	if (aws.i == 1)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (aws.i >= 2 && check_exit(final->cmd[1]))
	{
		printf("exit\n");
		// aws.e = (unsigned char)ft_atoi(final->cmd[1]);
		// // printf("%d\n", aws.e);
		// exit((int)aws.e);
		exit(ft_atoi(final->cmd[1])%256);
	}
	else if (aws.i >= 2 && !check_exit(final->cmd[1]))
	{
		printf ("minishell: exit: numeric argument required\n");
		exit(255);
	}
	else if (aws.i > 2 && check_exit(final->cmd[1]))
	{
		printf("exit\nminishell: exit: too many arguments\n");
		// status = 1;
	}
	else
		exit(EXIT_FAILURE);
	return (0);
}

int	builtincheck(char *name)
{
	if (!ft_strcmp(name, "echo") || !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"))
		return (1);
	return (0);
}

int	builtin(t_vars *var, t_final *final)
{
/*	◦ exit with no options */
	if (!ft_strcmp(final->cmd[0], "echo"))
		return (echo(var, final));
	else if (!ft_strcmp(final->cmd[0], "cd"))
		return (cd(var, final));
	else if (!ft_strcmp(final->cmd[0], "pwd"))
		return (pwd(var));
	else if (!ft_strcmp(final->cmd[0], "export"))
		return (export(var, final));
	else if (!ft_strcmp(final->cmd[0], "unset"))
		return (unset(var, final));
	else if (!ft_strcmp(final->cmd[0], "env"))
		return (environment(var, final));
	else if (!ft_strcmp(final->cmd[0], "exit"))
		return (exiting(var, final));
	return (0);
}

char	*exe_path_set(t_vars *var, char *exe)
{
	t_allways aws;

	aws.i = 0;
	while (var->exepath[aws.i])
	{
		if (!access(ft_strjoin(var->exepath[aws.i], exe), F_OK))
			return (ft_strjoin(var->exepath[aws.i], exe));
		aws.i++;
	}
	return (NULL);
}

/* void	runcmd(t_cmd *cmd, t_vars *var)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;

	// if (cmd == 0)
	// 	exit(0);

	if (cmd->type == EXEC)
	{
		ecmd = cmd->exe;
		size_t i = 0;
		if (ecmd->name[0] == 0)
			exit(0);
		if (builtincheck(ecmd->name))
		{
			builtin(var, ecmd);
			return ;
		}
		else
		{
			// execve(exe_path_set(var, ecmd->name), ecmd->args, var->env.newenv);
			execvp(exe_path_set(var, ecmd->name), ecmd->args);
			// execv(ft_strjoin("/usr/bin/", ecmd->name), ecmd->args);
			// perror("");
			printf("exec %s failed\n", ecmd->name);
		}
	}
	// else if (cmd->type == REDIR)
	// {
	// 	rcmd = cmd->red;
	// 	close(rcmd->fd);
	// 	if (open(rcmd->file, rcmd->mode) < 0){
	// 		printf("open %s failed\n", rcmd->file);
	// 		exit(0);
	// 	}
	// 	runcmd(rcmd->cmd, var);
	// }
	else if (cmd->type == PIPE)
	{
		pcmd = cmd->pip;
		// if (var->idx_fd > 0)
		// {
		// 	if (pipe(var->fd[var->idx_fd]) < 0)
		// 		trouble("pipe");
		// }
		if (fork1() == 0){
			// close(0);
			dup2(var->fd[var->idx_fd][1], 1);
			// close(p[0]);
			runcmd(pcmd->left, var);
			// close(p[1]);
		}
		if (fork1() == 0){
			// close(1);
			dup2(var->fd[var->idx_fd][0], 0);
			// close(p[1]);
			runcmd(pcmd->right, var);
			// close(p[0]);
		}
		// close(p[1]);
		// close(p[0]);
		wait(NULL);
		wait(NULL);
		// while (waitpid(-1, NULL, 0) < 0)
		// {}
		// exit(0);
	}
	else
		trouble("runcmd");
	// exit(0);
} */

void	fill_path(t_vars *var)
{
	t_allways aws;

	// if (!var->env.env[0])
	// 	return ;
	if (!check_env_var(var, "PATH"))
		trouble("fill_path");
	free1(var->temp);
	var->temp = ft_split(get_env_var(var, "PATH"), ':');
	var->exepath = malloc(sizeof(char *) * (ft_lstlen(var->temp) + 3));
	aws.i = 0;
	while (var->temp[aws.i])
	{
		var->exepath[aws.i] = ft_strjoin(var->temp[aws.i], "/");
		aws.i++;
	}
	var->exepath[aws.i] = ft_strdup("./");
	var->exepath[aws.i + 1] = ft_strdup("");
	var->exepath[aws.i + 2] = NULL;
}

void	initialisation(t_vars *var, char **env)
{
	var->tmp = malloc(sizeof(char));
	var->tmp1 = malloc(sizeof(char));
	var->tmp2 = malloc(sizeof(char));
	var->tmp3 = malloc(sizeof(char));
	var->temp = malloc(sizeof(char *));
	var->temp[0] = NULL;
	var->temp1 = malloc(sizeof(char *));
	var->temp2 = malloc(sizeof(char *));
	// var->buff = malloc(sizeof(char));
	var->env.env = env;
	
	var->tilda = ft_strdup("/Users/anajmi"); // ohrete
	// var->cmd = (t_cmd **)malloc(sizeof(t_cmd *) * FILENAME_MAX);
	var->cod = 0;
	// if (!env[0])
	// 	return;
	init_environment(var);
	init_export(var);
	fill_path(var);
}


/* int	main(int ac, char *av[], char **env)
{
	t_vars	*var;
	char	cwd[1024];

	var = malloc(sizeof(t_vars));
	initialisation(var, env);

	ft_export(var, "TEST_MINISHELL=0", 1);
	ft_export(var, "ENV_EXP_UNST=0", 1);
	ft_export(var, "ENV_EXP_UNST1=0", 1);
	ft_export(var, "ENV_EXP_UNST2=0", 1);
	ft_export(var, "ENV_EXP_UNST3=0", 1);
	ft_export(var, "ENV_EXP_UNST4=0", 1);
	show_env(var);
	printf("--------------------------------------------------------------------1\n");
	show_exp(var);
	printf("--------------------------------------------------------------------2\n");
	ft_unset(var, "TEST_MINISHELL");
	ft_unset(var, "ENV_EXP_UNST");
	ft_unset(var, "ENV_EXP_UNST1");
	ft_unset(var, "ENV_EXP_UNST4");
	ft_unset(var, "ENV_EXP_UNST3");
	ft_unset(var, "ENV_EXP_UNST2");
	show_env(var);
	printf("--------------------------------------------------------------------3\n");
	show_exp(var);
	printf("--------------------------------------------------------------------4\n");
	printf("%s\n", get_env_var(var, "PATH"));
	


	execv(ecmd->name, ecmd->args);

	fill_in_test0(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	fill_in_test1(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	fill_in_test2(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	one_pipe_fill_in_test(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	two_pipes_fill_in_test(var);
	runcmd(var->cmd[var->cod], var);
	++var->cod;
	
	while (1)
	{
		// chdir("..");
		getcwd(cwd, sizeof(cwd));
		free(var->temp);
		var->temp = ft_split(cwd, '/');
		if (ft_lstlen(var->temp) > 0)
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USER"), get_env_var(var, "HOSTNAME"), C_CYAN, var->temp[ft_lstlen(var->temp) - 1], C_RED, C_RES);
		else
			printf("%s$ %s%s@%s %s%s %s|%s", C_GREEN, C_YELOW, get_env_var(var, "USER"), get_env_var(var, "HOSTNAME"), C_CYAN, cwd, C_RED, C_RES);
		free(var->buff);
		var->buff = readline("→ ");
		add_history(var->buff);
		// printf("%s\n", var->buff);


		// fill_in_test3(var);
		// fill_in_test5(var);
		// fill_in_test0(var);
		// fill_in_test1(var);
		// two_pipes_fill_in_test0(var);
		// two_pipes_fill_in_test0test(var);
		one_pipe_fill_in_test0(var);
		// one_pipe_fill_in_test0test(var);
		system("leaks minishell");
		runcmd(var->cmd[var->cod], var);
		++var->cod;
		runPipedCommands(var);
		// fill_in_test2(var);
		// runcmd(var->cmd[var->cod], var);
		// ++var->cod;
	}
	return (0);
} */

