/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:49:47 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/01/07 17:04:32 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_builtins(t_data *data)
{
    if (ft_strncmp(data->args[0], "echo", 5) == 0)
        return (1);
    else if (ft_strncmp(data->args[0], "cd", 3) == 0)
        return (1);
    else if (ft_strncmp(data->args[0], "pwd", 4) == 0)
        return (1);
    else if (ft_strncmp(data->args[0], "unset", 6) == 0)
        return (1);
    else if (ft_strncmp(data->args[0], "env", 4) == 0)
        return (1);
    else if (ft_strncmp(data->args[0], "exit", 5) == 0)
        return (1);
    else if (ft_strncmp(data->args[0], "export", 7) == 0)
        return (1);
    return (0);
}


void ft_builtins_run(t_data *data, int prosses)
{
    int eta;
    
    eta = 0;
    if (data->files != NULL && prosses == 1)
        eta = file_redirection(data->files, prosses);

    if (eta == 1)
        get_shell_state()->exit_status = 1;    
    if (ft_strncmp(data->args[0], "echo", 5) == 0)
        get_shell_state()->exit_status = ft_echo(data);
    else if (ft_strncmp(data->args[0], "cd", 3) == 0)
        get_shell_state()->exit_status = ft_cd(data);
    else if (ft_strncmp(data->args[0], "pwd", 4) == 0)
        get_shell_state()->exit_status = ft_pwd();
    else if (ft_strncmp(data->args[0], "unset", 6) == 0)
        get_shell_state()->exit_status = ft_unset(data);
    else if (ft_strncmp(data->args[0], "env", 4) == 0)
        get_shell_state()->exit_status = ft_env(env_lst_to_tab(), prosses);
    else if (ft_strncmp(data->args[0], "exit", 5) == 0)
        ft_exit(data, prosses, &(get_shell_state()->exit_status));
    else if (ft_strncmp(data->args[0], "export", 7) == 0)
        ft_export(data, &(get_shell_state()->exit_status));
}

int files_dup(int num)
{
    int file;

    if (num == 0)
    {
        file = dup(STDIN_FILENO);
        if(file == -1)
            print_errore_exit("dup_error", 1);
    }
    if (num == 1)
    {
        file = dup(STDOUT_FILENO);
        if(file == -1)
            print_errore_exit("dup_error", 1);
    }   
    return (file);
}

int check_built(t_data *data, int prosses)
{
    int file[2];

    file[0] = files_dup(0);
    file[1] = files_dup(1);
    if (( data->args == NULL || *(data->args) == NULL))
    {
        print_errore("minishell: \n");
        if (data->files != NULL && prosses == 1)
        {
            get_shell_state()->exit_status = file_redirection(data->files, prosses);
            ft_dup2(file[0], 0);
            ft_dup2(file[1], 1);
            return (1);
        }        
    }
    if (is_builtins(data) == 1)
        ft_builtins_run(data, prosses);
    else
        return (0);
    if (prosses == 0)
        exit(get_shell_state()->exit_status ); // should be exit with ft_exit_clean !!!!
    ft_dup2(file[0], 0);
    ft_dup2(file[1], 1);
    return (1);
}
