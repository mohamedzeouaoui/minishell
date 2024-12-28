/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:26:03 by asodor            #+#    #+#             */
/*   Updated: 2024/12/28 10:16:11 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief This function expands the arguments and files in the command list
 * @brief It calls the ft_handle_expansions function to handle the expansions
 */

char *expand_env_var(char *str)
{
    //expand env var
    t_env *env;

    // if (str[0] == '?')
    // {
    //     return ft_itoa(get_shell_state()->exit_status);
    // }

    env = search_in_env(str);
    if (!env || !env->value)
        return ft_strdup("");
    return ft_strdup(env->value);
}

void ft_get_var_value(char *result, int *j, int *i, char *str)
{
    char *var_name;
    char *expansion;
    int k;
    int len;

    k = 0;
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '?'))
    {
        var_name[k] = str[*i];
        k++;
        (*i)++;
        if (str[*i - 1] == '?')
            break;
    }
    *i--;
    if (k > 0)
    {
        expansion = expand_env_var(var_name);
        len = ft_strlen(expansion);
        ft_memcpy(&result[*j], expansion, len);
        *j += len;
        free(expansion);
    }
    
}

char *ft_handle_expansions(char *str)
{
    char *result;         // Buffer to store the expanded string
    int i;               // Index for input string
    int j;               // Index for result string
    int quote;           // Keeps track of quote state (0 if not in quotes)

    result = mallocc(sizeof(char) * (ft_strlen(str) *2));  // Allocate double size for worst case
    i = 0;
    j = 0;
    quote = 0;
    
    while (str[i])
    {
        // Handle opening and closing quotes
        if ((str[i] == '\'' || str[i] == '\"') && !quote)  // Opening quote
        {
            quote = str[i];
            result[j++] = str[i++];
            continue;
        }else if (str[i] == quote)                         // Closing quote
        {
            quote = 0;
            result[j++] = str[i++];
            continue;
        }
        // Handle environment variable expansion
        if (str[i] == '$' && quote != '\'')                // Don't expand within single quotes
        {
            i++;
            if (str[i] == '?' || ft_isalnum(str[i]) || str[i] == '_')
                ft_get_var_value(result, &j, &i, str);     // Expand variable
            else
                result[j++] = '$';                         // Keep $ if not a valid variable
        } else
            result[j++] = str[i++];                    // Copy
        i++;
    }
    result[j] = '\0';                                    
    return result;
}

void ft_expand(t_data *cmd_list)
{
    t_data *current;
    t_files *files;
    int i;
    char *expanded;
    
    current = cmd_list;
    while (current)
    {
        i = 0;
        while (current->args && current->args[i])
        {
            expanded = ft_handle_expansions(current->args[i]);
            free(current->args[i]);
            current->args[i] = expanded;
            i++;
        }
        //expand files
        files = current->files;
        while (files)
        {
            if (files->file)
            {
                expanded = ft_handle_expansions(files->file);
                free(files->file);
                files->file = expanded;
            }
        }
        
        current = current->next;
    }                             
}

