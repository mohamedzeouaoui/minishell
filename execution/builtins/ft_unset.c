/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:25:19 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/12 06:25:22 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int env_free_node(char *key)
{
    t_env *head;
    t_env *tmp;

    while (head->next)
    {
        if(ft_strncmp(head->next->key, key, ft_strlen(key) + 1) == 0)
        {
            tmp = head->next;
            head->next = head->next->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            break;
        }
            head = head->next;
        }
    return (0);
}


int ft_unset(t_data *data)
{
    t_env *head;
    int i;

    i = 0;
    while (data->args[++i] != NULL)
    {
        head = get_shell_state()->env;
        if (head == NULL)
            return (0);
        if(ft_strncmp(data->args[i], "_", 2) == 0)
            continue;
        if(ft_strncmp(head->key, data->args[i], ft_strlen(data->args[i]) + 1) == 0)
        {
            get_shell_state()->env = head->next;
            free(head->key);
            free(head->value);
            free(head);
            continue;
        }
        env_free_node(data->args[i]);
    }
    return (0);
}
