/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:08:36 by asodor            #+#    #+#             */
/*   Updated: 2025/01/06 13:31:33 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
            if (files->redirection && !ft_strncmp(files->redirection, "<<", 3))
            {
                files->heredoc_fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
                if (files->heredoc_fd < 0)
                    return (1);
                while (1)
                {
                    files->file = readline("> ");
                    if (!files->file)
                        break;
                    if (!ft_strncmp(files->file, curr->args[0], ft_strlen(curr->args[0]) + 1))
                    {
                        free(files->file);
                        break;
                    }
                    write(files->heredoc_fd, files->file, ft_strlen(files->file));
                    write(files->heredoc_fd, "\n", 1);
                    free(files->file);
                }
                close(files->heredoc_fd);
                files->heredoc_fd = open("heredoc", O_RDONLY);
            }
            files = files->next;
        }
    }
}