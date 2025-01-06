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

int print_errore(char *err)
{
    if (err != NULL)
		write(STDERR_FILENO, err, ft_strlen(err));
    return(0);
}
int print_errore_exit(char *err, int exit_status)
{
    if (err != NULL)
		write(STDERR_FILENO, err, ft_strlen(err));
    exit(exit_status);// should be exit with ft_exit_clean !!!!
    return(0);
}

int print_errore_mix(char *error, char *error2, char *error3, int exit_status)
{
    print_errore(error);
    print_errore(error2);
    print_errore(error3);
    if (exit_status != 0 && exit_status != -1)
        exit(exit_status);
        //you should exite here with function exiterrr
    return(0);
}