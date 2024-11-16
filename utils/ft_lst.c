/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 02:50:25 by asodor            #+#    #+#             */
/*   Updated: 2024/11/16 02:29:53 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data  *ft_lstnew(void)
{
    t_data  *new;

    new = (t_data *)mallocc(sizeof(t_data));
    new->args = NULL;
    new->files = NULL;
    new->next = NULL;
    return (new);
}

t_data	*ft_lstlast(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*last;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
            new->next = NULL;
		}
	}
}