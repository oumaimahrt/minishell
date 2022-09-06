/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:52:39 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/06 21:00:29 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_output(t_final *s)
{
	t_final *final;
	t_file *file;
	t_cmd *cmd;
	int id = 1;
	final = s;
    while (final)
	{
		printf("output cmd number %d\n",id);
		cmd = final->name;
		while (cmd != NULL)
		{
			printf("name cmd is = %s and id is %d\n", cmd->str, id);
			cmd = cmd->next;
		}
		file = final->file;
		while (file != NULL)
		{
			printf("name file is = %s and id is = %d\n", file->str, file->id);
			file = file->next;
		}
		final= final->next;
		printf("end node number %d\n", id);
		id++;
	}
}



// void	free_cmdfinal(t_cmdfinal *cmd)
// {
// 	t_files		*tmp;
// 	t_cmdfinal	*pointer;
// 	t_cmdfinal	*fr;

// 	if (cmd->env)
// 		free(cmd->env);
// 	while (cmd != NULL)
// 	{
// 		pointer = cmd;
// 		fr = cmd;
// 		free_lines(cmd->tab);
// 		while (cmd->file)
// 		{
// 			tmp = cmd->file->next;
// 			free(cmd->file->name);
// 			free(cmd->file);
// 			cmd->file = tmp;
// 		}
// 		cmd = pointer->next;
// 		free(fr);
// 	}
// }


void	ft_free(t_final *cmd)
{
	t_file	*tmp;
	t_final	*pointer;
	t_final	*fr;
    t_cmd *name;

	while (cmd != NULL)
	{
		pointer = cmd;
		fr = cmd;
        while (cmd->name)
		{
			name = cmd->name->next;
			free(cmd->name->str);
			free(cmd->name);
			cmd->name = name;
		}
		while (cmd->file)
		{
			tmp = cmd->file->next;
			free(cmd->file->str);
			free(cmd->file);
			cmd->file = tmp;
		}
		cmd = pointer->next;
		free(fr);
	}
}


void ft_freetokens(t_token *data)
{
	t_token *tmp;
	t_token *node;

	while (data->next != NULL)
	{
		//printf("|%s|\n", data->str);
		tmp = data->next;
		//printf("%s\n", tmp->str);
		free(data->str);
		free(data);
		data = tmp;
	}
	printf("end free \n");
}

// void ft_freetokens(t_token *data)
// {
// 	t_token *tmp;
// 	t_token *node;
// 	t_token *new;

// 	new = data;

// 	while (new->next != NULL)
// 	{
// 		//printf("|%s|\n", data->str);
// 		tmp = new->next;
// 		printf("%s\n", new->str);
// 		printf("%p\n", new->str);
// 		free(new->str);
// 		free(new);
// 		new = tmp;
// 		new = new->next;
// 	}
// 	printf("end free \n");
// }
