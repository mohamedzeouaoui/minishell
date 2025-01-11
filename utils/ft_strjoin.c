/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 01:16:55 by asodor            #+#    #+#             */
/*   Updated: 2025/01/04 13:14:59 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2, size_t n)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (NULL == s1 && n >= 1)
		return (ft_strdup(s2));
	if (0 == n)
		n = ft_strlen(s2);
	join = (char *)mallocc((ft_strlen(s1) + (n + 1)) * sizeof(char));
	if (NULL == join)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0' && j < n)
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}
