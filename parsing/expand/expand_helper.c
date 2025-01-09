/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 07:12:16 by asodor            #+#    #+#             */
/*   Updated: 2025/01/09 20:34:56 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *expand_env_var(char *str)
{
    t_env *env;

    if (str[0] == '?')
        return ft_itoa(get_shell_state()->exit_status);

    env = search_in_env(str);
    if (!env || !env->value)
        return ft_strdup("");
    return ft_strdup(env->value);
}

char *get_var_name(t_helper *h, char *str)
{
    int k = 0;
    char *var_name;

    if (str[h->i] == '_')
    {
        var_name = ft_strdup("_");
        h->i++;
    }
    else if (str[h->i] == '?')
    {
        var_name = ft_strdup("?");
        h->i++;
    }
    else if (isdigit(str[h->i]))
    {
        var_name = ft_strdup("1");
        h->i++;
    }
    else
    {
        while (str[h->i] && (isalnum(str[h->i]) || str[h->i] == '_'))
        {
            k++;
            h->i++;
        }
        var_name = malloc(sizeof(char) * (k + 1));
        strncpy(var_name, &str[h->i - k], k);
        var_name[k] = '\0';
    }
    return var_name;
}

void copy_expansion(t_helper *h, char *expansion)
{
    int len;
    
    len = ft_strlen(expansion);
    memcpy(&h->result[h->j], expansion, len);
    h->j += len;
}

void ft_get_var_value(t_helper *h, char *str)
{
    char *var_name;
    char *expansion;

    var_name = get_var_name(h, str);
    
    if (!var_name)
        return;
    expansion = expand_env_var(var_name);
    if (!expansion)
    {
        free(var_name);
        return;
    }else
        h->from_env = 1;
    copy_expansion(h, expansion);
    // Adjust index to point to the character after the variable name
    // h->i--;
}

void ft_dollar_sign(t_helper *h, char *str)
{
    h->i++;
    if ((str[h->i] == '\"' && str[h->i - 2] == '\"') || str[h->i] == ' ' || str[h->i] == '$' || str[h->i] == '\0' || (str[h->i] == '\'' && str[h->i - 2] == '\'') )
    {
        h->result[h->j++] = '$';
        return ;
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