/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:05:50 by asodor            #+#    #+#             */
/*   Updated: 2024/12/06 17:06:30 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
    int size;
    
    j = 0;
    size = 0;
    while (env[*i] && env[*i] != '=')
    {
        (*i)++;
        j++;
    }
    if (env[*i] == '=' && env[*i - 1] == '+')
        j--;
    size = j;
    key = (char *)malloc(sizeof(char) * (size + 1));
    if (!key)
        return (NULL);
    j = 0;
    while (j < size)
    {
        key[j] = env[j];
        j++;
    }
    key[j] = '\0';
    (*i)++;
    return (key);
}

char *ft_value(char *env, int *i)
{
    char *value;
    int j;
    int start;
    
    j = 0;
    start = *i;
    while (env[*i])
    {
        (*i)++;
        j++;
    }
    value = (char *)malloc(sizeof(char) * (j + 1));
    if (!value)
        return (NULL);
    j = 0;
    while (env[start])
    {
        value[j] = env[start];
        start++;
        j++;
    }
    value[j] = '\0';
    return (value);
}