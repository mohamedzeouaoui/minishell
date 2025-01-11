/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:08:11 by asodor            #+#    #+#             */
/*   Updated: 2025/01/11 03:47:39 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
    **Maintain heap allocation list
    **Returns: Address of the static head pointer
*/

static	t_stack	**get_head(void)
{
	static t_stack	*head;

	return (&head);
}

/*
** Custom memory allocator that tracks allocations
** Stores allocated pointers in a linked list for later cleanup
** Exits program on allocation failure
** Returns: Pointer to allocated memory
*/

void	*mallocc(size_t size)
{
	t_stack	*new;
	t_stack	**head;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (new == NULL)
	{
		ft_print_err("minishell: allocation failed\n");
		exit_clean(1);
	}
	new->ptr = malloc(size);
	if (new->ptr == NULL)
	{
		free(new);
		ft_print_err("minishell: allocation failed\n");
		exit_clean(1);
	}
	head = get_head();
	if (new != NULL)
	{
		new->next = *head;
		*head = new;
	}
	return (new->ptr);
}

void	ft_clean(void)
{
	t_stack	**heap;
	t_stack	*tmp;

	heap = get_head();
	while (*heap != NULL)
	{
		tmp = *heap;
		(*heap) = (*heap)->next;
		free(tmp->ptr);
		free(tmp);
	}
}

static int	ft_check_add(t_stack **head, t_stack *tmp, void *ptr)
{
	if (ptr == tmp->ptr)
	{
		*head = tmp->next;
		free(tmp->ptr);
		free(tmp);
		return (1);
	}
	return (0);
}

void	ft_free_from_gc(void *ptr)
{
	t_stack	**head;
	t_stack	*tmp;
	t_stack	*to_delete;

	head = get_head();
	tmp = *head;
	if (tmp == NULL)
		return ;
	if (ft_check_add(head, tmp, ptr))
		return ;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->next->ptr == ptr)
		{
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			free(to_delete->ptr);
			free(to_delete);
			return ;
		}
		tmp = tmp->next;
	}
}
