/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:49:47 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/06 16:49:49 by mzeouaou         ###   ########.fr       */
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
    // else if (ft_strncmp(data->args[0], "export", 7) == 0)
    //     return (1);
    // else if (ft_strncmp(data->args[0], "unset", 6) == 0)
    //     return (1);
    else if (ft_strncmp(data->args[0], "env", 4) == 0)
        return (1);
    // else if (ft_strncmp(data->args[0], "exit", 5) == 0)
    //     return (1);
    return (0);
}


void ft_builtins_run(t_data *data, int prosses)
{
    if (ft_strncmp(data->args[0], "echo", 5) == 0)
        get_shell_state()->exit_status = ft_echo(data);
    else if (ft_strncmp(data->args[0], "cd", 3) == 0)
        get_shell_state()->exit_status = ft_cd(data);
    else if (ft_strncmp(data->args[0], "pwd", 4) == 0)
        get_shell_state()->exit_status = ft_pwd();
    // else if (ft_strncmp(data->args[0], "unset", 6) == 0)
    //     get_shell_state()->exit_status = ft_unset(data);
    else if (ft_strncmp(data->args[0], "env", 4) == 0)
        get_shell_state()->exit_status = ft_env(env_lst_to_tab(), prosses);
    // else if (ft_strncmp(data->args[0], "exit", 5) == 0)
    //     ft_exit(data, prosses, &(get_shell_state()->exit_status));
    // else if (ft_strncmp(data->args[0], "export", 7) == 0)
    //     ft_export(data, &(get_shell_state()->exit_status));
}


int cheack_built(t_data *data, int prosses)
{
    if (is_builtins(data) == 1)
        ft_builtins_run(data, prosses);
    

}

   
