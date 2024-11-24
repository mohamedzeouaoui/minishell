/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:06:49 by asodor            #+#    #+#             */
/*   Updated: 2024/11/24 03:05:50 by asodor           ###   ########.fr       */
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
	char	*err;
	(void)f;
	err = NULL;
	if(s1)
		err = ft_strjoin(err, s1, ft_strlen(s1));
	if (s2)
		err = ft_strjoin(err, s2, ft_strlen(s2));
	if (s3)
		err = ft_strjoin(err, s3, ft_strlen(s3));
    
	if (err != NULL)
		ft_print_err(err);
	//if (code != -1 && code != 0)
		//exiter(code);
}
