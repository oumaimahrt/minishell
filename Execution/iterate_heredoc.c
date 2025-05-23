/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:41:54 by anajmi            #+#    #+#             */
/*   Updated: 2022/10/04 11:25:21 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc_pipe(t_vars *var, t_final **node, t_file *file)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (trouble("pipe", NULL, "can't open heredoc", 1));
	if ((*node)->herein != -1 && (*node)->herein != 0)
		close((*node)->herein);
	heredoc(var, file->str, fd);
	close(fd[1]);
	(*node)->herein = fd[0];
	if (g_status == 1)
		return (1);
	return (0);
}

int	iterate_heredoc(t_vars *var, t_final **node)
{
	t_file		*file;
	t_final		**save;

	save = node;
	while ((*node))
	{
		file = (*node)->file;
		(*node)->h = 0;
		while (file)
		{
			if (file->id == 4)
			{
				(*node)->h++;
				if (heredoc_pipe(var, node, file))
				{
					node = save;
					return (1);
				}
			}
			file = file->next;
		}
		node = &(*node)->next;
	}
	node = save;
	return (0);
}
