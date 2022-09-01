/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:50:30 by ohrete            #+#    #+#             */
/*   Updated: 2022/09/02 00:16:10 by ohrete           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//The Parser is the software component that reads the command line such as “ls -­al” 
//and puts it into a data structure called C​ommand Table ​that will store the commands that will be executed.

t_token	*create_node(void)
{
	t_token	*new_node;
	
	new_node =  (t_token *)malloc(sizeof (t_token));
	new_node->my_node = NULL;
	new_node->next = NULL;
	new_node->after_pipe = 0;
	new_node->before_pipe = 0;
	new_node->append = NULL;
	new_node->here_d = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->cmd = NULL;
	new_node->content = NULL;
	return (new_node);
}

t_token	*new_content(void *content)
{
	t_token	*new_node;
	
	new_node =  (t_token *)malloc(sizeof (t_token));
	new_node->my_node = NULL;
	new_node->after_pipe = 0;
	new_node->before_pipe = 0;
	new_node->append = NULL;
	new_node->here_d = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->cmd = NULL;
	new_node->content = content;
	new_node->id = 0;
	new_node->next = NULL;
	return (new_node);
}

// void	add_last_list(t_token **head, t_token *new)
// {
// 	t_token	*last;

// 	last = (*head);
// 	if (!(*head))
// 		(*head) = new;
// 	else
// 	{
// 		while (last->next != NULL)
// 			last = last->next;
// 		last->next = new;
// 	}
// }

void	add_first_list(t_token **list, t_token *new)
{
	if (!new || !list)
		return ;
	new->next = *list;
	*list = new;
}

t_token	*last_elem(t_token *list)
{
	t_token	*tmp;

	if (!list)
		return (NULL);
	tmp = list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	add_last_list(t_token **list, t_token *new)
{
	t_token	*last;

	if (!(*list))
	{
		add_first_list(list, new);
		return ;
	}
	last = last_elem(*list);
	if (new->next == NULL)
		last->next = new;
	while (new->next != NULL)
	{
		last->next = new;
		new = new->next;
	}
}

int	list_size(t_token *list)
{
	t_token	*tmp;
	int	i;
	
	if (!list)
		return (0);
	i = 1;
	tmp = list;
	while(tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	clear_list(t_token **list)
{
	t_token	*tmp;

	if (!(*list))
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	list = NULL;
}
 
int	my_errors(int e)
{
	if (e == 1)
		printf("Oops Error! Syntax error!\n");
	return (0);
}

void	 my_cmds(t_token **head)
{
	int	i;
	int	len;
	t_token	*tmp_head;
	t_token	*tab;

	tmp_head = *head;
	printf("before while \n");
	while (tmp_head)
	{
		tab = tmp_head->my_node;
		i = 0;
		len = list_size(tab);
		tmp_head->cmd = malloc((len + 1) * sizeof (char *));
		printf("my table\n");
		while(tab)
		{
			tmp_head->cmd[i] = ft_strdup(tab->content);
			i++;
			tab = tab->next;
		}
		printf("after strdup\n");
		tmp_head->cmd[i] = NULL;
		tmp_head = tmp_head->next;
	}
	printf("after while \n");
}

void	redirects(t_token	**line, t_token **head)
{
	if ((*line)->id == INPUT)
	{
		if (!(*line)->next)
			my_errors(1);
		printf("input\n");
		(*head)->infile = ft_strdup((*line)->next->content);
		printf("inputfile\n");
	}
	else if ((*line)->id == OUTPUT)
	{
		if (!(*line)->next)
			my_errors(1);
		(*head)->outfile = ft_strdup((*line)->next->content);
	}
	else if ((*line)->id == HERE_DOC)
	{
		if (!(*line)->next)
			my_errors(1);
		(*head)->here_d= ft_strdup((*line)->next->content);
	}
	else if ((*line)->id == APPEND)
	{
		if (!(*line)->next)
			my_errors(1);
		(*head)->append = ft_strdup((*line)->next->content);
	}
	(*line) = (*line)->next->next;
}

void	my_pipe(t_token **line, t_token **head)
{
	if (!(*head) || !(*line)->next)
		my_errors(1);
	(*line) = (*line)->next;
	(*head)->after_pipe = 1;
	add_last_list(head, create_node());
	(*head) = (*head)->next;
	(*head)->before_pipe = 1;
}

t_token *parser(t_token **line)
{
	t_token	*str;
	t_token	*head;
	t_token	*tmp;

	str = *line;
	head = create_node();
	tmp = head;
	printf("======>before str\n");
	while (str)
	{
		if (str->id == PIPE)
		{
			printf("======>PIPE\n");
			my_pipe(&str, &head);
		}
		else if (str->id == WORD)
		{
			printf("======>WORD\n");
			add_last_list(&(head->next), new_content((str->content)));
			printf("hallo \n");
			str = str->next;
		}
		else
		{
			printf("======>redirects\n");
			redirects(&str, &head);
		}
		printf("OUT \n");
	}
	printf("======>making array\n");
	my_cmds(&tmp);
	printf("clearing my list\n");
	clear_list(line);
	printf("final\n");
	line = 0;
	return (tmp);
}

// void	parsing(char *line, t_env *env)
// {
// 	t_token	*tokens;
// 	t_node	*cmd;

// 	cmd = (t_node *)malloc(sizeof(t_node));
	
	
// }