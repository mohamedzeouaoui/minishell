/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 02:50:25 by asodor            #+#    #+#             */
/*   Updated: 2024/10/26 05:43:33 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data  *ft_lstnew(void)
{
    t_data  *new;

    new = (t_data *)malloc(sizeof(t_data));
    new->args = NULL;
    new->files = NULL;
    new->next = NULL;
    return (new);
}
