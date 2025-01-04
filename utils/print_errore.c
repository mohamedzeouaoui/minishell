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
    char *message;
    char *var;


    printf("%s%s%s\n", error, error2, error3);

    // message = ft_strjoin(message, error, ft_strlen(error));
    // var = message;
    // message = ft_strjoin(message, error2, ft_strlen(error2));
    // //ft_free(var);
    // var = message;
    // message = ft_strjoin(message, error3, ft_strlen(error3));
    // //ft_free(var);
    // if(message != NULL)
    //     print_errore(message);
    if (exit_status != 0 && exit_status != -1)
        exit(exit_status);
        //you should exite here with function exiterrr
    return(0);
}