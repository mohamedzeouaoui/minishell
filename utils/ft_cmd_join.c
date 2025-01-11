/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:51:52 by asodor            #+#    #+#             */
/*   Updated: 2025/01/11 00:10:56 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_cmd_join(char **original_arr, char *new_str)
{
	int		len;
	char	**new_arr;

	len = 0;
	if (!new_str)
		return (original_arr);
	if (!original_arr)
	{
		new_arr = (char **)mallocc(sizeof(char *) * 2);
		new_arr[0] = ft_strdup(new_str);
		new_arr[1] = NULL;
		return (new_arr);
	}
	while (original_arr[len++])
		;
	new_arr = (char **)mallocc(sizeof(char *) * (len + 2));
	len = 0;
	while (original_arr[len])
	{
		new_arr[len] = ft_strdup(original_arr[len]);
		len++;
	}
	new_arr[len] = ft_strdup(new_str);
	new_arr[len + 1] = NULL;
	return (new_arr);
}
