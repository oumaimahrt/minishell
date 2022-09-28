/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:52:39 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/28 15:41:39 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*convert_char_str(char c)
{
	char	*str;

	str = malloc (sizeof (char) * 2);
	if (!str)
	{
		ft_putstr_fd("error allocation\n", 2);
		return (NULL);
	}
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_token	*ft_lstlast1(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	check_last_word(t_token **temp, t_save *save)
{
	t_token	*tmp;

	tmp = *temp;
	if (!ft_strcmp(ft_lstlast1(tmp)->str, PIPE)
		|| !ft_strcmp(ft_lstlast1(tmp)->str, "A")
		|| !ft_strcmp(ft_lstlast1(tmp)->str, "H")
		|| !ft_strcmp(ft_lstlast1(tmp)->str, "W")
		|| !ft_strcmp(ft_lstlast1(tmp)->str, "<")
		|| !ft_strcmp(ft_lstlast1(tmp)->str, ">"))
		save->error = trouble(NULL, NULL, "syntax error", 258);
}

int allspaces(char *line)
{
	int i;
	 
	i = 0;
	while(line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return(1);
}

// void	check_last_word(t_token **temp, t_save *save)
// {
// 	t_token	*tmp;

// 	tmp = *temp;
// 	if (!ft_strcmp(ft_lstlast1(tmp)->str, PIPE)
// 		|| !ft_strcmp(ft_lstlast1(tmp)->str, "A")
// 		|| !ft_strcmp(ft_lstlast1(tmp)->str, "H")
// 		|| !ft_strcmp(ft_lstlast1(tmp)->str, "W")
// 		|| !ft_strcmp(ft_lstlast1(tmp)->str, "<")
// 		|| !ft_strcmp(ft_lstlast1(tmp)->str, ">"))
// 		save->error = trouble(NULL, NULL, "syntax error", 258);
// }

void ft_output(t_final *s)
{
	t_final *final;
	t_file *file;
	char **cmd;
	int id = 1;
	int		i;
	final = s;
    while (final)
	{
		i = 0;
		printf("output cmd number %d\n",id);
		cmd = final->cmd;
		while (cmd[i])
		{
			printf("name cmd is = %s and id is %d\n", cmd[i], id);
			i++;
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

// void free_tokens(t_token *data)
// {
// 	t_token *tmp;
// 	t_token *node;

// 	while (data->next != NULL)
// 	{
// 		printf("|%s|\n", data->str);
// 		tmp = data->next;
// 		printf("%s\n", tmp->str); // **** sefault hna
// 		free(data->str);
// 		free(data);
// 		data = tmp;
// 	}
// 	printf("end free \n");
// }

// void free_tokens(t_token *data)
// {
// 	t_token *tmp;
// 	t_token *new;

// 	new = data;

// 	while (new != NULL)
// 	{
// 		//printf("|%s|\n", data->str);
// 		tmp = new->next;
// 		//#printf("%s\n", new->str);
// 		//#printf("%p\n", new->str);
// 		//printf("%s\n",new->next->str);
// 		//printf("%p\n",new->next->str);
// 		free(new->str);
// 		free(new);
// 		new = tmp;
// 	}
// 	//#printf("end free \n");
// }