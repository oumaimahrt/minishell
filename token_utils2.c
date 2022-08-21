/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:30:42 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/21 21:58:36 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *str,t_env *env, char **av)
{
	int		i;
	int		start;
	char	*ptr;
	char	*new;

	i = 0;
	start = 0;
	new = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] != '\0' && str[i + 1] == '?')
			{
				ptr = ft_itoa(g_status);
				new = ft_strjoin(new, ptr);
				i = i + 2;
			}
			else if (str[i + 1] != '\0' && str[i + 1] == 48)
			{
				ptr = ft_strdup(av[0]);
				new = ft_strjoin(new, ptr);
				i = i + 2;
			}
			else
			{
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			ptr = ft_substr(str, start, i - start);
			ptr = getting_env(env, ptr);
			//printf("ptr = %s\n",ptr);
			new = ft_strjoin(new, ptr);
			//printf("if=======|%s|\n",new);
			}
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			ptr = ft_substr(str, start, i - start); //fixing single quotes
			new = ft_strjoin(new, ptr);
			//printf("else=======|%s|\n",new);
		}
	}
	printf("=======%s\n",new);
	return (new);
}
