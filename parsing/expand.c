/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:26:03 by asodor            #+#    #+#             */
/*   Updated: 2024/12/13 23:53:58 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void expand(t_data *cmd_list)
{
    t_data	*current;
    int		i;

    current = cmd_list;
    while (current)
    {
        i = 0;
        while (current->args && current->args[i])
        {
            if (ft_strcmp(current->args[0], "export") == 0)
                current->args[i] = expand_word(current->args[i]);
            i++;
        }
        current = current->next;
    }
}
