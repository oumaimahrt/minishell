/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 23:18:46 by anajmi            #+#    #+#             */
/*   Updated: 2022/09/23 21:37:10 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_check(char *args)
{
	t_allways	aws;

	aws.j = 1;
	while (args[aws.j])
	{
		if (args[aws.j] != 'n')
			return (1);
		aws.j++;
	}
	return (0);
}

static int	echo_core(t_final *node, t_allways aws)
{
	if (node->cmd[aws.i][0] == '-' && node->cmd[aws.i][1])
	{
		while (node->cmd[aws.i] && node->cmd[aws.i][0] == '-'
			&& !echo_check(node->cmd[aws.i]))
		{
			aws.k = 0;
			aws.i++;
		}
	}
	while (node->cmd[aws.i])
	{
		ft_putstr_fd(node->cmd[aws.i], node->outfile);
		aws.i++;
		if (node->cmd[aws.i])
			ft_putchar_fd(' ', node->outfile);
	}
	return (aws.k);
}

int	echo(t_final *node)
{
	t_allways	aws;

	aws.i = 1;
	aws.k = 1;
	if (node->cmd[aws.i])
		aws.k = echo_core(node, aws);
	if (aws.k)
		ft_putchar_fd('\n', node->outfile);
	return (0);
}
