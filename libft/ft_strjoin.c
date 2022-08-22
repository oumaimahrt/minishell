/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:33:51 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/22 21:43:52 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"
// char	*ft_strjoin(char*s1, char *s2)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	len;
// 	char	*dest;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen((char *) s1) + ft_strlen(s2);
// 	dest = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!dest)
// 		return (NULL);
// 	while (s1[i])
// 		dest[j++] = s1[i++];
// 	i = 0;
// 	while (s2[i])
// 		dest[j++] = s2[i++];
// 	dest[j] = '\0';
// 	if (s1)
// 		free(s1);
// 	if (s2)
// 		free(s2);
// 	return (dest);
// }

static char    *ft_copy(char const *s1, char const *s2, char *p)
{
    int    i;
    int    j;

    i = 0;
    j = 0;
    while (s1[i] != '\0')
    {
        p[i] = s1[i];
        i++;
    }
    while (s2[j] != '\0')
    {
        p[i] = s2[j];
        j++;
        i++;
    }
    p[i] = '\0';
    return (p);
}

char    *ft_strjoin(char *s1, char *s2)
{
    unsigned int    total;
    int                i;
    int                j;
    char            *p;

    // if (!s1 || !s2)
    // return (NULL);
    // if (!s2)
    //     return (NULL);
    total = 0;
    i = 0;
    j = 0;
	printf("str join start \n");
    total = ft_strlen(s1) + ft_strlen(s2) + 1;
    p = malloc((total) * sizeof(char));
    if (p == NULL)
        return (NULL);
    p = ft_copy(s1, s2, p);
    printf("str join bfore \n");
	if (s1 != NULL)
        free(s1);
		printf("str join between \n");
    if (s2 != NULL)
        free(s2);
	printf("str join fin \n");
    return (p);
}

// #include<stdio.h>
// int main()
// {
// 	printf("%s\n", ft_strjoin("hello","world"));
// }