/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:06:24 by ohrete            #+#    #+#             */
/*   Updated: 2022/08/17 20:35:58 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int counting_line(char **line)
// {
//     int i;

//     i = 0;
//     while(line[i])
//         i++;
//     return (i);
// }

// char	**copy_env(char **env)
// {
//     char    **table;
//     //char    **split;
//     int     i;

//     i = 0;
//     //printf("%d\n",counting_line(env));
//     table = malloc(sizeof(char *) * counting_line(env) + 1);
//     while (env[i])
//     {
//         table[i] = ft_strdup(env[i]);
//         printf("%s\n",table[i]);
//         i++;
//     }
//     table[i] = 0;
//     return (table);
// }

char    *search_name(char *name, int i)
{
    char    *str;
    int     len;
    char    *c;

    c = ft_strchr(name, i);
   // printf("c ==> [%s]\n",c);
    len = ft_strlen(c);
    str = ft_substr(name, 0, ft_strlen(name) - len);
    
    return (str);
}

char    *search_value(char *name, int i)
{
    char    *str;
    int     len;
    char    *c;

    c = ft_strchr(name, i);
    len = ft_strlen(c);
    str = ft_substr(name, ft_strlen(name) - len + 1, len);
    return (str);
}

t_env   *fill_struct(char *name, char *value)
{
    t_env *new;
    
    new = malloc(sizeof(t_env));
    new->name = name;
    new->value = value;
    new->next = NULL;
    return (new);
}

void    add_first(t_env **fst_link, t_env *new)
{
    if (!new || !fst_link)
        return ;
    new->next = *fst_link;
    *fst_link = new;
}

// t_env   *search_last(t_env *fst_link)
// {
//     t_env *tmp;
    
//     if (!fst_link)
//         return (NULL);
//     tmp = fst_link;
//     while (tmp->next != NULL)
//         tmp = tmp->next;
//     return (tmp);
// }

// void    add_last(t_env **fst_link, t_env *new)
// {
//     t_env *last;
    
//     if (!(*fst_link))
//     {
//         add_first(fst_link, new);
//         return ;
//     }
//     last = search_last(*fst_link);
//     if(new->next == NULL)
//         last->next = new;
//     while (new->next != NULL)
//     {
//         last->next = new;
//         new = new->next;
//     }
// }

void add_last(t_env **head, t_env *new)
{
    t_env *last;
    
    last = (*head);
    if (!(*head))
        (*head) = new;
    else
    {
        while (last->next)
            last = last->next;
        last->next = new;
    }
}

void    expansion_env(t_env **fst_link, char **env)
{
    //t_env **line;
    char *name;
    char *value;
    int     i;
    //char    **table;
    //char    **split;
    // char *s;

    //line = NULL;
    //table = copy_env(env);
    i = 0;
    // split = ft_split(env[i], '=');
    while(env[i])
    {
        name = search_name(env[i], '=');
       // printf("name ==> [%s]\n",name);
        value = search_value(env[i], '=');
        //printf("value ==> [%s]\n",value);
        add_last(fst_link, fill_struct(name, value));
        //printf("hahahahahhahahahahahah\n");
        i++;
    }
}
