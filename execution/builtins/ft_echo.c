/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:50:40 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/06 16:50:43 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int test_n_flag(t_data *data, int *i)
{
    int n_flag;
    int j;

    n_flag = 0;
    (*i) = 1;
    while (data->args[*i] && ft_strncmp(data->args[*i], "-n", 2) == 0)
    {
        j = 2;
        while (data->args[*i][j] == 'n')
            j++;
        if (data->args[*i][j] != '\0')
            break;
        else
            n_flag = 1;
        (*i)++;
    }
    return (n_flag);
}


int ft_echo(t_data *data)
{
    int i;
    int n_flag;
    int j;

    i = 1;
    n_flag = test_n_flag(data, &i);
    write(STDOUT_FILENO, &i, 1);
    while (data->args[i])
    {
        j = 0;
        while (data->args[i][j] != '\0')
        {
            if(data->args[i][j] != '\n' || n_flag == 0)
                write(STDOUT_FILENO, &data->args[i][j], 1);
            j++;
        }
        i++;
        if (data->args[i])
            write(STDOUT_FILENO, " ", 1);
    }
    if (n_flag == 0)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}        




