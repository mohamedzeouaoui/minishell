/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:08:36 by asodor            #+#    #+#             */
/*   Updated: 2025/01/07 17:47:47 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_get_value(int *i, char *str, char **result)
{
    char *var_name;
    char *expansion;

    var_name = ft_get_name(i,str);
    if (!var_name)
        return;
    expansion = expand_env_var(var_name);
    if (!expansion)
    {
        free(var_name);
        return;
    }
    *result =  ft_strjoin(*result, expansion, ft_strlen(expansion));
    free(expansion);
    free(var_name);
    // Adjust index to point to the character after the variable name
}


char *ft_expand_line(char *line)
{
    char *expanded_line;
    int i;

    expanded_line = ft_strdup("");
    i = 0;
    while (line[i])
    {
        if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_' || line[i + 1] == '?'))
        {
            i++;
            ft_get_value(&i, line, &expanded_line);
        }
        else
        {
            expanded_line = ft_strjoin(expanded_line, &line[i], 1);
            i++;
        }
    }
    return (expanded_line);
}

void ft_read_and_write(int fd[2], char *delimiter)
{
    char *line;
    int ret;

    close(fd[p_outp]);
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            ft_print_err("warning: here-document delimited by end-of-file\n");
            break;
        }
        if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
        {
            free(line);
            break;
        }
        line = ft_expand_line(line);
        write(fd[p_inp], line, ft_strlen(line));
        write(fd[p_inp], "\n", 1);
        free(line);
    }
    close(fd[p_inp]);
    exit(0);
}

int ft_open_heredoc(char *delimiter)
{
    int fd[2];
    int pid;
    int status;

    if(pipe(fd) == -1)
    {
        ft_print_err("pipe error\n");
        exit(1); // exit and clean 
    }
    pid = fork();
    if (pid == -1)
    {
        ft_print_err("fork error\n");
        exit(1); // exit and clean 
    }
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        ft_read_and_write(fd, delimiter);
    }
    waitpid(-1, &status, 0);
    get_shell_state()->exit_status = WEXITSTATUS(status);
    close(fd[p_inp]);
    // if (get_shell_state()->exit_status == 130 || get_shell_state()->exit_status == 131)
		// return (-1);
    return (fd[p_outp]);
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
