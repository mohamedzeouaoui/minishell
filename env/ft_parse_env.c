/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:30:27 by asodor            #+#    #+#             */
/*   Updated: 2024/12/06 17:11:52 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *ft_key_value(char *env)
{
    t_env *new;
    char *key;
    char *value;
    int i;
    
    i = 0;
    key = ft_key(env, &i);
    value = ft_value(env, &i);
    new = ft_env_new_node(key, value);
    return (new);
}

void ft_add_env(t_env **env, t_env *new)
{
    t_env *tmp;
    
    if (!*env)
    {
        *env = new;
        return;
    }
    tmp = *env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
void	ft_parse_env(char **env, t_shell *shell)
{
    int		i;
    t_env	*new;

    i = 0;
    while (env[i])
    {
        new = ft_key_value(env[i]);
        ft_add_env(&shell->env, new);
        i++;
    }
}

