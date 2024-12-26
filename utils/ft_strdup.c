/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 06:03:29 by asodor            #+#    #+#             */
/*   Updated: 2024/11/24 03:39:54 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_strdup(const char *s1)
{
    char	*str;
    size_t	len;
    size_t	i;
    if (!s1)
        return NULL;
        
    len = ft_strlen(s1);
    str = (char *)mallocc(len + 1);
    if (!str)
        return (NULL);
    i = 0;

    while(i <= len){
        str[i] = s1[i];
        i++;
    }

    return str;
}

char    *ft_strdup_normal(const char *s1)
{
    char	*str;
    size_t	len;
    size_t	i;
    if (!s1)
        return NULL;
        
    len = ft_strlen(s1);
    str = (char *)mallocc(len + 1);
    if (!str)
        return (NULL);
    i = 0;

    while(i <= len){
        str[i] = s1[i];
        i++;
    }
    return str;
}
