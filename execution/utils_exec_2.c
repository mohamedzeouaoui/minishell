/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:10:58 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/01/10 17:11:02 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dirctory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
	{
		print_errore_mix("minishell: ", path, " no such file or directory\n",
			127);
		return (1);
	}
	if (S_ISDIR(sb.st_mode))
	{
		print_errore_mix("minishell: ", path, " is a directory\n", 126);
		return (1);
	}
	return (0);
}
