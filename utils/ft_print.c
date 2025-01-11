/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:06:49 by asodor            #+#    #+#             */
/*   Updated: 2025/01/11 00:11:59 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

int	ft_print_err(char *err)
{
	if (err != NULL)
		write(STDERR_FILENO, err, ft_strlen(err));
	return (0);
}

void	ft_print_err1(char *s1, char *s2, char *s3, int f)
{
	ft_print_err(s1);
	ft_print_err(s2);
	ft_print_err(s3);
	if (f != -1 && f != 0)
		exit_clean(f);
}
