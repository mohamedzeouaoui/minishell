/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:51:14 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/06 16:51:17 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int ft_isnumber(const char *str)
{
    if (!str || *str == '\0')
        return (0);

    // Handle optional leading sign
    if (*str == '-' || *str == '+')
        str++;

    // Check if the rest of the string is composed of digits
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }

    return (1);
}

void ft_exit(t_data *data, int prosses, int *exit_status)
{
    int i;

    (void)prosses;
    i = 0;
    while (data->args[i])
        i++;
    if (i > 2)
    {
        print_errore_mix("exit", " too many arguments", NULL, 1);
        return ;
    }
    if (i == 1)
        exit(0);
    if (ft_isnumber(data->args[1]) == 0)
    {
        print_errore_mix("exit", " numeric argument required", data->args[1], 255);
        return ;
    }
    (*exit_status) = atoi(data->args[1]);
    exit(atoi(data->args[1]));
}
