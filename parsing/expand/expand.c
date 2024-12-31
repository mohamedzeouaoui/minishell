/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:26:03 by asodor            #+#    #+#             */
/*   Updated: 2024/12/31 09:49:25 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief This function expands envirement variables in a string
 * @param str The string containing the envirement variable reference
 * @return The expanded string
 */

char *expand_env_var(char *str)
{
    t_env *env;

    if (str[0] == '?')
        return ft_strdup("exit_status");

    env = search_in_env(str);
    if (!env || !env->value)
        return ft_strdup("");
    return ft_strdup(env->value);
}

void ft_get_var_value(char *result, int *j, int *i, char *str)
{
    int k = 0;
    char *var_name;
    char *expansion;
    int len;

    if (str[*i] == '?')
    {
        var_name = ft_strdup("?");
        (*i)++;
    }
    else if (isdigit(str[*i]))
    {
        var_name = malloc(sizeof(char) * 2);
        if (!var_name)
            return;
        var_name[0] = str[*i];
        var_name[1] = '\0';
        (*i)++;
    }
    else
    {
        // Handle valid variable names (letters, underscores, etc.)
        while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
        {
            k++;
            (*i)++;
        }

        var_name = malloc(sizeof(char) * (k + 1));
        if (!var_name)
            return;

        strncpy(var_name, &str[*i - k], k);
        var_name[k] = '\0';
    }

    expansion = expand_env_var(var_name);
    len = ft_strlen(expansion);

    memcpy(&result[*j], expansion, len);
    *j += len;
    free(expansion);
    free(var_name);
    (*i)--; // Adjust index to point to the character after the variable name
}


void ft_init_helper(t_helper *helper, char *str)
{
    helper->i = 0;
    helper->j = 0;
    helper->quote = 0;
    helper->result = mallocc(sizeof(char) * (ft_strlen(str) + 1));
    if (!helper->result)
        return;
}
void ft_handle_quotes(t_helper *h, char *str)
{
    while (str[h->i] && (str[h->i] == '\'' || str[h->i] == '\"'))
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
            h->result[h->j++] = str[h->i++];
    }
}

void ft_dollar_sign(t_helper *h, char *str)
{
    h->i++;
    if (str[h->i] == '?' || isalnum(str[h->i]) || str[h->i] == '_')
        ft_get_var_value(h->result, &h->j, &h->i, str);
    else
    {
        h->result[h->j++] = '$';
        if (str[h->i])
            h->result[h->j++] = str[h->i];
    }
    h->i++;
}

char *ft_handle_expansions(char *str)
{
    t_helper *h;

    h = mallocc(sizeof(t_helper));
    ft_init_helper(h, str);
    while (str[h->i])
    {
        ft_handle_quotes(h, str);
        // Handle environment variable expansion
        if (str[h->i] == '$' && (h->quote != '\'')) // Don't expand within single quotes
            ft_dollar_sign(h, str);
        else
            h->result[h->j++] = str[h->i++];
    }
    h->result[h->j] = '\0';
    return h->result;
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
        current = current->next;
    }
}
