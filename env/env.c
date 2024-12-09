/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 00:27:25 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/09 00:27:28 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **env_lst_to_tab(void)
{
    t_env *head;
    char **env1;
    int i;

    i = 0;
    head = get_shell_state()->env;
    env1 = (char **)mallocc(sizeof(char *) * (ft_lstsize(head) + 1));
    if (!env1)
        return (NULL);
    while (head)
    {
        if (head->value)
        {
            env1[i] = ft_strjoin(head->key , "=", 1);
            env1[i] = ft_strjoin(env1[i], head->value, ft_strlen(head->value));
        }
        i++;        
        head = head->next;
    }
    env1[i] = NULL;
    return (env1);
}
