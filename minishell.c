/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:26:50 by ohrete            #+#    #+#             */
/*   Updated: 2022/07/22 11:26:51 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
    char	*str;

    (void)ac;
    (void)av;
	while (1)
	{
		str = readline("minishell>");
		if (!str)
		{
			printf("exit");
			exit(0);
		}
	}
}