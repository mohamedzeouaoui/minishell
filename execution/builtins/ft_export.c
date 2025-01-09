/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:56:14 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/01/09 16:55:27 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_exported_vars(void)
{
    char **export_env;
    int i;
    int j;
    
    j = -1;
    export_env = export_env_sorted();
    while (export_env[++j])
    {
        if (ft_strncmp(export_env[j], "_=", 2) != 0)
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

int check_variable_valid(char *variable)
{
    int i;
    
    i = 0;

    if (!ft_isalpha(variable[i]) && variable[i] != '_')
    {
        print_errore_mix("minishell: export: `", variable,"': not a valid identifier\n", -1);
        return(1);
    }
    while (variable[++i] && variable[i] != '=')
    {
        if (variable[i + 1] == '=' && variable[i] == '+')
            return (1);
        if (!ft_isalnum(variable[i]) && variable[i] != '_')
        {
            print_errore_mix("minishell: export: `", variable,"': not a valid identifier\n", -1);
            return(1);
        }
    }
    return (0);
}

int allocate_variable(char *variable, char **var)
{
    int i;
    int count;
    
    i = 0;
    while (variable[i] && variable[i] != '=' && variable[i] != '+')
        i++;
    (*var) = (char *)mallocc(sizeof(char) * (i + 1));
    count = i;
    i = -1;
    while (++i < count)
        (*var)[i] = variable[i];
    (*var)[i] = '\0';
    return (count);
}

void append_env(char *var, char *value)
{
    t_env *tmp;
    char *new_value;
    
    tmp = search_in_env(var);
    new_value = (char *)mallocc(sizeof(char) * (ft_strlen(tmp->value) + ft_strlen(value) + 1));
    new_value = ft_strcpy(new_value, tmp->value);
    new_value = ft_strcat(new_value, value);
    free(tmp->value);
    tmp->value = new_value;
}

void add_to_export(char *var, char *value)
{
    t_env *tmp;
    char *val;
    
    tmp = search_in_env(var);
    val = (char *)mallocc(sizeof(char) * ft_strlen(value) + 1);
    val = ft_strcpy(val, value);
    if (tmp == NULL)
        ft_add_env(&get_shell_state()->env, ft_env_new_node(var, val));
    else
    {
        free(tmp->value);
        tmp->value = val;
    }
}

void export_variables(char *variable)
{
    int j;
    char *var;
    char *value;
    
    check_variable_valid(variable);
    if (ft_strncmp(variable, "_", 2) == 0)
        return ;
    j = allocate_variable(variable, &var);
    if (variable[j] == '+')
    {
        if (search_in_env(var) == NULL)
        {
            value = (char *)mallocc(sizeof(char) * ft_strlen(variable + j + 2) + 1);
            value = ft_strcpy(value, variable + j + 2);
            ft_add_env(&get_shell_state()->env, ft_env_new_node(var, value));
        }
        else
            append_env(var, variable + j + 2);
    }
    else
        add_to_export(var, variable + j + 1);
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
   while (data->args[++i] != NULL)
   {
        export_variables(data->args[i]);
   }
   
        
}
