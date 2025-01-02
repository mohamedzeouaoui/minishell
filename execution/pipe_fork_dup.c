/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:20:15 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/31 15:20:17 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_dup2(int fd1, int fd2)
{
    if (dup2(fd1, fd2) == -1)
        print_errore_exit("dup2_error\n", 1);
    return (0);
}


void files_pipe(int fd_pipe[2], int fd_stdout_stored, int size, int i)
{
    if (size <= 1)
        return ;    
    if (i == 0)
    {
        ft_dup2(fd_pipe[p_inp], 1);
        close(fd_pipe[p_inp]); // ft_close
        close(fd_pipe[p_outp]); // ft_close
    }
    else if (i != 0 && i != size - 1)
    {
        ft_dup2(fd_pipe[p_inp], 1);
        close(fd_pipe[p_inp]);
        ft_dup2(fd_stdout_stored, 0);
        close(fd_stdout_stored);
        close(fd_pipe[p_outp]);
    }
    else if (i == size - 1)
    {
        ft_dup2(fd_stdout_stored, 0);
        close(fd_stdout_stored);
    }
    return ;
}

