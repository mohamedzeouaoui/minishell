/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:30:27 by asodor            #+#    #+#             */
/*   Updated: 2024/12/05 23:50:09 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *ft_env_new_node(char *k, char *v)
{
    t_env *new;

    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = k;
    new->value = v;
    new->next = NULL;
    return (new);
}

char *ft_key(char *env, int *i)
{
    char *key;
    int j;

    j = 0;
    while (env[*i] && env[*i] != '=' || (env[*i] == '+' && env[*i + 1] == '='))
    {
        (*i)++;
        j++;
    }
    key = (char *)malloc(sizeof(char) * (j + 1));
    if (!key)
        return (NULL);
    j = 0;
    while (env[*i] && env[*i] != '=' || (env[*i] == '+' && env[*i + 1] == '='))
    {
        key[j] = env[*i];
        (*i)++;
        j++;
    }
    key[j] = '\0';
    if (env[*i] == '+')
        (*i)++;
    return (key);
}
char *ft_value(char *env, int *i)
{
    char *value;
    int j;

    j = 0;
    while (env[*i])
    {
        (*i)++;
        j++;
    }
    value = (char *)malloc(sizeof(char) * (j + 1));
    if (!value)
        return (NULL);
    j = 0;
    while (env[*i])
    {
        value[j] = env[*i];
        (*i)++;
        j++;
    }
    value[j] = '\0';
    return (value);
}

t_env *key_value(char *env)
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

void add_env(t_env **env, t_env *new)
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
    t_env	*tmp;

    i = 0;
    while (env[i])
    {
        new = ft_key_value(env[i]);
        ft_add_env(&shell->env, new);
        i++;
    }
}

