/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:18:48 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/01/03 12:18:51 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sort_env_alphabetically(char **env, int size)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (i < size)
    {
        j = i + 1;
        while(j < size)
        {
            if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
            {
                tmp = env[i];
                env[i] = env[j];
                env[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

char **export_env_sorted(void)
{
    t_env *tmp;
    char **env;
    int i;

    i = 0;
    tmp = get_shell_state()->env;
    env = (char **)malloc(sizeof(char *) * (ft_lstsize_env(tmp) + 1));
    if (!env)
        return (NULL);
    while (tmp)
    {
        env[i] = ft_strjoin(tmp->key, "=", 0);
        env[i] = ft_strjoin(env[i], tmp->value, 0);
        i++;
        tmp = tmp->next;
    }
    env[i] = NULL;
    sort_env_alphabetically(env, ft_lstsize_env(get_shell_state()->env));
    return (env);
}
