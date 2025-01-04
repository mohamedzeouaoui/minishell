/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:38:29 by asodor            #+#    #+#             */
/*   Updated: 2025/01/04 18:39:07 by asodor           ###   ########.fr       */
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
            if (str[h->i] == '$' && (h->quote != '\'')) // Don't expand within single quotes
                ft_dollar_sign(h, str);
            else
                h->result[h->j++] = str[h->i];
            h->i++;
        }
    }
}