/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:32:52 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/18 18:13:38 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((unsigned char)s1[i] != '\0' || (unsigned char)s2[i] != '\0')
		&& (i < n))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
				i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while(*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
			s1++;
			s2++;
	}
	return (0);
}

// #include<stdio.h>
// int main()
// {
// 	char a[15] = "helloworld";
// 	char b[20] = "helloastrhvclkdt";
// 	printf("%d\n",ft_strncmp(a,b,6));
// }