/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:01:19 by dantonik          #+#    #+#             */
/*   Updated: 2022/10/19 22:17:27 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_tail(t_head **head, char *str, int type)
{
	t_node	*new;
	t_node	*current;

	new = (t_node *)malloc(sizeof(t_node));
	(*head)->length++;
	new->cmnd = ft_strtrim(str, " ");
	new->type = type;
	new->next = NULL;
	current = (*head)->head;
	if ((*head)->head == NULL)
	{
		(*head)->head = new;
		new->prev = NULL;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
	(*head)->tail = new;
}

void	free_list(t_head *a)
{
	t_node	*temp;

	temp = a->head;
	while (temp != NULL)
	{
		a->head = a->head->next;
		free (temp);
		temp = a->head;
	}
	free(a);
}

void	printl(t_head *head)
{
	t_node	*current;
	int		i;

	i = 0;
	if (head == NULL)
		return ;
	current = head->head;
	while (current != NULL)
	{
		printf("___%s___ [%u], invalid: %d\n", current->cmnd, current->type, current->invalid);
		i++;
		current = current->next;
	}
	printf("\n\t--> %i elements.\n", i);
}

void	printl_rev(t_head *head)
{
	t_node	*current;
	int		i;

	i = 0;
	if (head == NULL)
		return ;
	current = head->head;
	while (current->next != NULL)
		current = current->next;
	while (current != NULL)
	{
		printf("___%s___ [%u]\n", current->cmnd, current->type);
		i++;
		current = current->prev;
	}
	printf("\n\t--> %i elements.\n", i);
}
