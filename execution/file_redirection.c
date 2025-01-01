/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:44:31 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/31 14:44:35 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int input_file_clear(t_files *file)
{
    int fd;

    fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        print_errore("minishell: ");
        perror(file->file);
        return (1);
    }
    // store the file descriptor in the file struct
    ft_dup2(fd, 1);
    close(fd);
    return (0);
}


int input_file_append(t_files *file)
{
    int fd;

    fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        print_errore("minishell: ");
        perror(file->file);
        return (1);
    }
    // store the file descriptor in the file struct
    ft_dup2(fd, 1);
    close(fd);
    return (0);
}

int file_redirection(t_files *file, int prosses)
{
    int exit_status;
    int i;

    i = 0;
    
    if (file == NULL)
        return (1);    
    while (file != NULL)
    {
        if (ft_strncmp(file->redirection, ">", 1) == 0)
            exit_status = input_file_clear(file);
        else if (ft_strncmp(file->redirection, ">>", 2) == 0)
            exit_status = input_file_append(file);
        // else if (ft_strncmp(file->redirection, "<", 1) == 0 )
        //     //output_file(file->file);
        // else if (ft_strncmp(file->redirection, "<<", 2) == 0)
        //     //heredoc
        if (exit_status == 1)
        {
            if (prosses == 1)
                return (1);
            exit(1); //ft_exit_clean(1);
        }
        file = file->next;
    }
    return (0);
}