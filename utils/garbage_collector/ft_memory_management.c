/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:08:11 by asodor            #+#    #+#             */
/*   Updated: 2025/01/09 13:57:24 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
    **Maintain heap allocation list
    **Returns: Address of the static head pointer
*/

static  t_stack    **get_head(void)
{
    static t_stack *head;
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