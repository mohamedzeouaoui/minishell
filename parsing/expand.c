/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:26:03 by asodor            #+#    #+#             */
/*   Updated: 2024/12/27 04:01:48 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Check if character is a valid expansion character
** Returns 1 if true, 0 if false
*/

void ft_replace_word(char *word, int *i)
{
    int j;
    int k;
    char *var_name;
    char *var_value;
    
    j = *i + 1;
    k = 0;
    while (ft_isalpha(word[j]) || ft_isdigit(word[j]) || word[j] == '_')
    {
        j++;
        k++;
    }
    var_name = ft_substr(word, *i + 1, k);
    var_value = ft_getenv(var_name);
    if (var_value == NULL)
    {
        var_value = "";
    }
    word = ft_strjoin(ft_substr(word, 0, *i), var_value);
    word = ft_strjoin(word, ft_substr(word, j, ft_strlen(word) - j));
    *i = *i + ft_strlen(var_value);
}

void   ft_no_qutoes(char *word)
{
    int i;
    
    i = 0;
    while (word[i])
    {
        if (word[i] == '$')
        {
            while (ft_isdigit(word[i+1]))
                i++;
        }
        
        i++;
    }
}

char    *expand_word(char *word)
{
    ft_no_qutoes(word);
    
    return (word);
}

void expand(t_data *cmd_list)
{
    t_data	*current;
    int		i;

    current = cmd_list;
    while (current)
    {
        if (ft_strcmp(current->args[0], "export") == 0)
        {
            i = 1;
            while (current->args[i])
            {
                current->args[i] = expand_word(current->args[i]);
                i++;
            }
        }
        current = current->next;
    }
}
