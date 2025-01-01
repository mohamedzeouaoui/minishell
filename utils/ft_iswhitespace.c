/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:55:06 by asodor            #+#    #+#             */
/*   Updated: 2024/11/14 02:56:24 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// return 1 if c is a white space, otherwise returns 0
int	ft_iswhitespace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
