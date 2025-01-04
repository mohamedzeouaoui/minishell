/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:26:03 by asodor            #+#    #+#             */
/*   Updated: 2025/01/04 13:48:49 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief This function expands envirement variables in a string
 * @param str The string containing the envirement variable reference
 * @return The expanded string
 */

void ft_init_helper(t_helper *helper, char *str)
{
    helper->i = 0;
    helper->j = 0;
    helper->quote = 0;
    helper->from_env = 0;
    helper->result = mallocc(sizeof(char) * (ft_strlen(str) + 1));
    if (!helper->result)
        return;
}
void ft_handle_quotes(t_helper *h, char *str);

void ft_dollar_sign(t_helper *h, char *str)
{
    h->i++;
    if (str[h->i] == '\"' || str[h->i] == ' ' || str[h->i] == '$' || str[h->i] == '\0')
    {
        h->result[h->j++] = '$';
    }
    if ((str[h->i] == '?' || isalnum(str[h->i]) || str[h->i] == '_'))
        ft_get_var_value(h, str);
    else
    {
        ft_handle_quotes(h, str);
        if (str[h->i])
            h->result[h->j++] = str[h->i++];
    }
}

void ft_handle_quotes(t_helper *h, char *str)
{
    while (str[h->i])
    {
        if ((str[h->i] == '\'' || str[h->i] == '\"') && !h->quote) // Opening quote
        {
            h->quote = str[h->i++];
        }
        else if (str[h->i] == h->quote) // Closing quote
        {
            h->quote = 0;
            h->i++;
        }
        else
        {
            if (str[h->i] == '$' && (h->quote != '\'')) // Don't expand within single quotes
                ft_dollar_sign(h, str);
            else
                h->result[h->j++] = str[h->i];
            h->i++;
        }
    }
}
// Change return type to char**

char **ft_handle_expansions(char *str, int flag)
{
    t_helper *h;
    char **result_arr;
    int i;

    h = malloc(sizeof(t_helper));  // Fix typo: mallocc -> malloc
    if (!h)
        return NULL;  // Handle allocation failure

    ft_init_helper(h, str);
    ft_handle_quotes(h, str);
    h->result[h->j] = '\0';

    if (flag == 1)
    {
        result_arr = ft_split(h->result, ' ');
        free(h);  // Free the helper struct, h->result is part of the split
    }
    else
    {
        result_arr = malloc(2 * sizeof(char*));  // Allocate space for two pointers
        if (!result_arr)
        {
            free(h);  // Free the helper struct if allocation fails
            return NULL;
        }
        result_arr[0] = h->result;
        result_arr[1] = NULL;
        free(h);  // Free the helper struct, h->result is in result_arr
    }
    return result_arr;
}
void ft_expand_args(t_data *current)
{
    int i;
    int j;
    char **expanded_args;
    char **new_args;
    
    i = 0;
    new_args = NULL;
    while (current->args && current->args[i])
    {
        expanded_args = ft_handle_expansions(current->args[i++], 1);
        if (expanded_args && *expanded_args)
        {
            j = 0;
            while (expanded_args[j])
                new_args = ft_cmd_join(new_args, expanded_args[j++]);
        }
        // Don't free expanded_args here since ft_cmd_join handles the memory
    }
    //ft_free_array(current->args);  // Free old args only
    current->args = new_args;
}

void ft_expand_files(t_files *files)
{
    t_files *current;
    char **new_file;
    
    current = files;
    while (current && current->file)
    {
        new_file = ft_handle_expansions(current->file, 0);
        if (new_file && *new_file)
        {
            free(current->file);  // Free old file name
            current->file = new_file[0];  // Take ownership of first string
            free(new_file);  // Only free the array, not its contents
        }
        current = current->next;
    }
}

void ft_expand(t_data *cmd_list)
{
    t_data *current;
    t_files *files;
    int i;
    char **expanded_args;

    current = cmd_list;
    while (current)
    {
        ft_expand_args(current);
        ft_expand_files(current->files);
        current = current->next;
    }
}
