/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:20:15 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/01/11 04:35:27 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		print_errore_exit("dup2_error\n", 1);
	return (0);
}

void	files_pipe(int fd_pipe[2], int fd_stdout_stored, int size, int i)
{
	if (size <= 1)
		return ;
	if (i == 0)
	{
		ft_dup2(fd_pipe[P_INP], 1);
		close(fd_pipe[P_INP]);
		close(fd_pipe[P_OUTP]);
	}
	else if (i != 0 && i != size - 1)
	{
		ft_dup2(fd_stdout_stored, 0);
		close(fd_stdout_stored);
		ft_dup2(fd_pipe[P_INP], 1);
		close(fd_pipe[P_INP]);
		close(fd_pipe[P_OUTP]);
	}
	else if (i == size - 1)
	{
		ft_dup2(fd_stdout_stored, 0);
		close(fd_stdout_stored);
	}
	return ;
}
