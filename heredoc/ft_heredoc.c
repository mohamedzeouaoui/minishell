/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:08:36 by asodor            #+#    #+#             */
/*   Updated: 2025/01/06 17:15:58 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_open_heredoc(char *delimiter)
{
    int fd[2];
    int pid;

    pid = safe_fork();
    if (pid == 0)
        ft_myfunction(fd, delimiter);
    
    return (fd);
}

int ft_heredoc(t_data *cmd_list)
{
    t_data *curr;
    t_files *files;

    curr = cmd_list;
    while(curr)
    {
        files = curr->files;
        while (files)
        {
            if (files->file && !ft_strncmp(files->redirection, "<<", 3))
            {
                files->heredoc_fd = ft_open_heredoc(files->file);
                if (files->heredoc_fd == -1)
                    return (0);
                return (1);
            }else
                files->heredoc_fd = -1;
            files = files->next;
        }
        curr = curr->next;
    }
    return (1);
}