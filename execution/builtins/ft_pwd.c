/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:04:22 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/12 06:04:24 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_pwd(t_data *data)
{
    char *path;

    path = getcwd(NULL, 0);
    if(path == NULL && get_shell_state()->pwd != NULL)
        printf("%s\n", get_shell_state()->pwd);
    else if (path == NULL && get_shell_state()->pwd == NULL)
    {
        print_errore_mix("pwd: error retrieving current directory:",
			"getcwd: cannot access parent directories: ",
			"No such file or directory", -1);
        return (1);
    }
    else
    {
        printf("%s\n", path);
        free(path);
    }
    return (0);
}
