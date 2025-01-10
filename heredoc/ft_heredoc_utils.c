/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:10:24 by asodor            #+#    #+#             */
/*   Updated: 2025/01/10 23:41:36 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_get_name(int *i, char *str)
{
    int k = 0;
    char *var_name;

    if ((str[*i] == '_' && str[*i + 1] == '\0') || str[*i] == '?' || ft_isdigit(str[*i]))
    {
        var_name = ft_strdup(str + *i);
        (*i)++;
    }
    else
    {
        while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        {
            k++;
            (*i)++;
        }
        var_name = malloc(sizeof(char) * (k + 1));
        ft_strncpy(var_name, &str[*i - k], k);
        var_name[k] = '\0';
    }
    return var_name;
}
