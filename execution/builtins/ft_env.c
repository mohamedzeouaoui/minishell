/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:50:59 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/06 16:51:02 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_env(char **env, int prosses)
{
    int i;

    i = 0;
    (void)prosses;
    while(env != NULL && env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }

    return (0);
}
