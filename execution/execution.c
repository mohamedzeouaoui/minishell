/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:00:38 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/06 17:00:43 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int command_execution(t_data *data, int size)
{
    command_not_found(data);
    if (check_slash_in_path(data->args[0]) == true)
        check_run_path_not_commande(data->args[0], data);
    else
        check_in_env_path_cmd(data->args[0], data);
    exit(get_shell_state()->exit_status); // should be exit with ft_exit_clean !!!!
    //ft_exit_clean(get_shell_state()->exit_status);
    return (0);
}


void run_command_in_child_process(t_data *data, int *id_child, int size, int i)
{
    int fd_pipe[2];
    int fd_stdout_stored;

    if (size > 1 && i < size - 1)
    {
        if (pipe(fd_pipe) == -1)
            print_errore_exit("pipe_error\n", 1);
    }
    if ((id_child[i] = fork()) == -1)
        print_errore_exit("fork_error\n", 1);
    if (id_child[i] == 0)
    {
        if (check_built(data, 0) == 0)
        {
            files_pipe(fd_pipe, fd_stdout_stored, size, (i));
            if(data->files != NULL)
                file_redirection(data->files, 0);
            if (is_builtins(data) == 0)
                command_execution(data, size);
        }
        exit(get_shell_state()->exit_status);
    }
    if (i != size - 1)
        close(fd_pipe[p_inp]);
    if (i > 0)
        close(fd_pipe[p_outp]);
    fd_stdout_stored = fd_pipe[p_outp];
}

void    ft_exec(t_data *data, int size)
{
    int i;
    int *id_child;
    
    // t_shell *shell;

    if (check_built(data, 1) == 1 && size == 1)
        return ;
    id_child = (int *)mallocc(sizeof(int) * size);
    get_shell_state()->exit_status = 0;
    i = 0;
    while (i < size && data != NULL)
    {
        run_command_in_child_process(data, id_child, size, i);
        data = data->next;
        i++;
    }
    int status;
    waitpid(-1, &status, 0);
    
}
