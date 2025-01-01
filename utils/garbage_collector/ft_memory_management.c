/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:08:11 by asodor            #+#    #+#             */
/*   Updated: 2024/11/16 02:51:39 by asodor           ###   ########.fr       */
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

void    *mallocc(size_t size)
{
    t_stack    *new_node;
    t_stack    **head;
    void    *allocated_memory;

    // Allocate tracking node
    new_node = (t_stack *)malloc(sizeof(t_stack));
    // Allocate requested memory
    allocated_memory = malloc(size);
    new_node->ptr = allocated_memory;
    head = get_head();
    new_node->next = *head;
    *head = new_node;
    return (allocated_memory);
}