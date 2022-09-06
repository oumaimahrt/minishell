/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:50:30 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/06 20:59:19 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirect(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	if (ft_strcmp(str, ">") == 0)
		return (2);
	if (ft_strcmp(str, ">>") == 0)
		return (3);
	if (ft_strcmp(str, "<<") == 0)
		return (4);
	return (0);
}

t_final	*create_node(void)
{
	t_final	*new_node;
	
	new_node =  (t_final *)malloc(sizeof (t_final));
	if (!new_node)
		return (NULL);
	// new_node = NULL;
	new_node->next = NULL;
	// new_node->file = NULL;
	// new_node->name = NULL;
	//printf("creat big node \n");
	return (new_node);
}

t_file	*file_node(char *str, int type)
{
	t_file	*new_node;
	// t_file	*link_file;

	// link_file = NULL;
	
	new_node =  (t_file *)malloc(sizeof (t_file));
	if (!new_node)
		return (NULL);
	// new_node = NULL;
	new_node->next = NULL;
	// if (file == NULL)
	// {
	// 	printf("head of file \n");
	// 	file = new_node;
	// 	link_file = new_node;
	// }
	// else
	// {
	// 	printf("NOT head of file \n");
	// 	link_file->next = new_node;
	// 	link_file = new_node;
	// }
	new_node->str = ft_strdup(str);
	new_node->id = type;
	//printf("creat file node \n");
	return (new_node);
}


// void    creat_node(t_node *head, char *data)
// {
//     t_node    *new;
//     t_node    last_node;

//     new = (t_node)malloc(sizeof(t_node));
//     if (!new)
//         return ;
//     new->data = ft_strdup(data);
//     new->next = NULL;
//     if (*head == NULL)
//         head = new;
//     else
//     {
//         last_node =head;
//         while (last_node->next != NULL)
//         {
//             last_node = last_node->next;
//         }
//                 last_node->next = new;
//     }
// }

t_cmd	*cmd_node(char *str)
{
	t_cmd	*new_node;
	// t_cmd *link_cmd;
	
	//link_cmd = NULL;
	new_node =  (t_cmd *)malloc(sizeof (t_cmd));
	if (!new_node)
		return (NULL);
	//new_node = NULL;
	// if (*name == NULL)
	// {
	// 	printf("head of cmd\n");
	// 	*name = new_node;
	// 	link_cmd = new_node;
	// }
	// else
	// {
	// 	printf("NOT head of cmd \n");
	// 	link_cmd->next = new_node;
	// 	link_cmd = new_node;
	// }
	new_node->str = ft_strdup(str);
	new_node->next = NULL;
	//printf("|%s| \n", (*name)->str);
	//printf("creat cmd node \n");
	return (new_node);
}

t_final	*ft_parser(t_token *data)
{
	t_final *head;
	t_final *tmp;
	t_final *link;
	t_token *save;
	t_file *save_file;
	t_file *node_file;
	t_cmd *save_cmd;
	t_cmd *node_cmd;
	int		type;

	head = NULL;
	save = data;
	while (data)
	{
		tmp = create_node();
		//printf("koko \n");
		if (head == NULL)
		{
			//printf("head \n");
			head = tmp;
			link = head;
			tmp->file = NULL;
			tmp->name = NULL;
		}
		else
		{
			//printf("not head \n");
			link->next = tmp;
			link = tmp;
			tmp->file = NULL;
			tmp->name = NULL;
		}
		// printf("before whileweee %s\n", data->str);
		// printf("inside first while \n");
		while (data && strcmp(data->str, "|") != 0)
		{
			//printf("starting \n");
			if (redirect(data->str))
			{
				tmp->type = FIL;
				type = redirect(data->str);
				data = data->next;
				node_file = file_node(data->str, type);
				if (tmp->file == NULL)
				{
					//printf("if of head file \n");
					tmp->file = node_file;
					save_file = node_file;
				}
				else
				{
					//printf("else of not head file\n");
					save_file->next = node_file;
					save_file = node_file;
				}
			}
			else
			{
				tmp->type = NAM;
				node_cmd = cmd_node(data->str);
				if (tmp->name == NULL)
				{
					//printf("IF \n");
					tmp->name = node_cmd;
					save_cmd = node_cmd;
					//printf(" IF END\n");
				}
				else
				{
					//printf("ELSE \n");
					save_cmd->next = node_cmd;
					save_cmd = node_cmd;
				}
				// /printf("********* |%s|\n", tmp->name->str);
			}
			data = data->next;
		}
		//printf("000\n");
		if (tmp->name)
			node_cmd->next = NULL;
		if (tmp->file)
			node_file->next = NULL;
			//printf("1111 \n");
		if (data != NULL)
			data = data->next;
	}
	//printf("endd\n");
	tmp->next = NULL;
	return (head);
}