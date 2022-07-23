/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:33:51 by ohrete            #+#    #+#             */
/*   Updated: 2021/11/23 04:50:09 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen((char *) s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = '\0';
	return (dest);
}
// #include<stdio.h>
// int main()
// {
// 	printf("%s\n", ft_strjoin("hello","world"));
// }