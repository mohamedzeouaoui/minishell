/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:56:14 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/12 06:56:16 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_exported_vars(void)
{
    char **export_env;
    t_env *tmp;
    int i;
    int j;
    
    j = -1;
    export_env = export_env_sorted();
    while (export_env[++j])
    {
        if (ft_strncmp(export_env[j], "_", 1) != 0)
        {
            printf("declare -x ");
            i = -1;
            while (export_env[j][++i])
            {
                printf("%c", export_env[j][i]);
                if (export_env[j][i] == '=' && export_env[j][i + 1] != '\0')
                {
                    printf("\"%s\"",  export_env[j] + i + 1);
                    break;
                }
            }
            printf("\n");
        }
    }
}


void    ft_export(t_data *data, int *exit_status)
{
    int i;

    if (data->args[1] == NULL)
    {
        print_exported_vars();
        *exit_status = 0;
        return ;
    }
    i = 0;
   
        
}
