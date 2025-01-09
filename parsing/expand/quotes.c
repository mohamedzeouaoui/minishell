/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:38:29 by asodor            #+#    #+#             */
/*   Updated: 2025/01/09 20:36:19 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
            if (str[h->i] == '$' && (h->quote != '\''))// Don't expand within single quotes {
                ft_dollar_sign(h, str);
            else
            {
                h->result[h->j++] = str[h->i];
                h->i++;
            }
        }
    }
}

char **ft_remove_quotes(char *file)
{
    int i;
    int j;
    int quote;
    char **result;

    i = 0;
    j = 0;
    quote = 0;
    result = malloc(2 * sizeof(char *));
    result[0] = malloc(sizeof(char) * (ft_strlen(file) + 1));
    while (file[i])
    {
        if ((file[i] == '\'' || file[i] == '\"') && !quote)
            quote = file[i++];
        else if (file[i] == quote)
        {
            quote = 0;
            i++;
        }else
            result[0][j++] = file[i++];
    }
    result[0][j] = '\0';
    result[1] = NULL;
    return result;
}
