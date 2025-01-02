/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:26:03 by asodor            #+#    #+#             */
/*   Updated: 2025/01/02 17:51:42 by asodor           ###   ########.fr       */
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

char *ft_handle_expansions(char *str)
{
    t_helper *h;

    h = mallocc(sizeof(t_helper));
    ft_init_helper(h, str);
    ft_handle_quotes(h, str);
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
