/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:34:24 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/11 18:34:27 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int print_errore(char *error)
{
    ft_putstr_fd(error, STDERR_FILENO);
    return(0);
}


print_errore_mix(char *error, char *error2, char *error3, int exit_status)
{
    char *message;
    char *var;

    message = ft_strjoin(message, error, ft_strlen(error));
    var = message;
    message = ft_strjoin(message, error2, ft_strlen(error2));
    //ft_free(var);
    var = message;
    message = ft_strjoin(message, error3, ft_strlen(error3));
    //ft_free(var);
    if(message != NULL)
        print_errore(message);
    if (exit_status != 0 && exit_status != -1)
        exiter(exit_status);
    return(0);
}