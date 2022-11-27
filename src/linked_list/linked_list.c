/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:38:05 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 03:10:16 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_token_tail(t_head **head, char *str, int type)
{
	t_node	*new;
	t_node	*current;

	new = (t_node *)malloc(sizeof(t_node));
	(*head)->length++;
	trim_leading_char(str, ' ');
	trim_trailing_char(str, ' ');
	remove_dup_c(str, ' ');
	new->cmnd = str;
	new->type = type;
	new->next = NULL;
	new->cmnd_path = NULL;
	new->t_builtin = 0;
	new->head = (*head);
	new->pos = (*head)->length;
	current = (*head)->head;
	if ((*head)->head == NULL)
		return ((*head)->head = new, (*head)->tail = new, \
		new->prev = NULL, free_list(NULL));
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
	(*head)->tail = new;
}

void	free_list(t_head *a)
{
	t_node		*temp;
	t_env_node	*env_temp;

	if (a == NULL)
		return ;
	temp = a->head;
	while (temp != NULL)
	{
		a->head = a->head->next;
		free(temp->cmnd);
		free (temp);
		temp = a->head;
	}
	free(a);
}

void	printl(t_head *head)
{
	t_node	*current;

	if (head == NULL)
		return ;
	current = head->head;
	while (current != NULL)
	{
		printf("___%s___\t[pos:%i]\t[type:%u]\t[builtin:%u]\n", \
			current->cmnd, current->pos, current->type, current->t_builtin);
		current = current->next;
	}
}

void	free_list_loop(t_head **a)
{
	t_node	*temp;

	temp = (*a)->head;
	while (temp != NULL)
	{
		(*a)->head = (*a)->head->next;
		free (temp->cmnd);
		free (temp->cmnd_path);
		free (temp);
		temp = (*a)->head;
	}
	(*a)->head = NULL;
}