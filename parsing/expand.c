/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:26:03 by asodor            #+#    #+#             */
/*   Updated: 2024/12/07 03:00:48 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// Handle single quotes
static void ft_single_quote(char *arg, char **res, int *i, int preserve_quotes)
{
    int end;

    // Add opening quote if preserving quotes
    if (preserve_quotes)
        *res = ft_strnjoin(*res, arg + (*i), 1);
    
    // Find closing quote
    end = ++(*i);
    while (arg[end] != '\'' && arg[end])
        end++;
    
    // Copy content between quotes
    *res = ft_strnjoin(*res, ft_substr(arg, *i, end - *i), 0);
    
    // Add closing quote and update index
    if (arg[end] == '\'')
    {
        if (preserve_quotes)
            *res = ft_strnjoin(*res, arg + end, 1);
        *i = ++end;
    }
}

// Handle double quotes
static void ft_double_quote(char *arg, char **res, int *i, int preserve_quotes)
{
    int end;

    // Add opening quote if preserving quotes
    if (preserve_quotes)
        *res = ft_strnjoin(*res, arg + (*i), 1);
    
    end = ++(*i);
    // Process until closing quote
    while (arg[end] != '\"' && arg[end])
    {
        if (arg[end] == '$' && ft_isalpha(arg[end + 1]))
            ft_expand_variable(arg, res, &end);
        else
            *res = ft_strnjoin(*res, arg + end++, 1);
    }
    
    // Add closing quote and update index
    if (arg[end] == '\"')
    {
        if (preserve_quotes)
            *res = ft_strnjoin(*res, arg + end, 1);
        *i = ++end;
    }
}

// Handle variable expansion
static void ft_expand_variable(char *arg, char **res, int *i)
{
    int start;
    char *var_name;
    char *var_value;

    start = ++(*i);
    // Get variable name
    while (ft_isalnum(arg[*i]) || arg[*i] == '_')
        (*i)++;
    
    // Extract variable name and get its value
    var_name = ft_substr(arg, start, *i - start);
    var_value = getenv(var_name);
    
    // Add value if exists
    if (var_value)
        *res = ft_strnjoin(*res, var_value, 0);
    
    free(var_name);
}

// Updated quote_checker function
void quote_checker(char *arg, char **res, int *i, int q)
{
    if (arg[*i] == '\'')
        ft_single_quote(arg, res, i, q);
    else if (arg[*i] == '\"')
        ft_double_quote(arg, res, i, q);
    else
        ft_expand_variable(arg, res, i);
}


int	heredoc(t_data *data, int *i, char **res)
{
	if (ft_strncmp(data->files->redirection, "<<", 3) != 0 && data->files->file)
	{
		while (data->files->file[*i])
			quote_checker(data->files->file, res, i, 1);
		if (*res == NULL)
			data->files->heredoc_fd = -1;
		if (data->files->file[0] != '\"' && data->files->file[0] != '\''
			&& !check_res_whitepaces(*res))
			data->files->heredoc_fd = -1;
		*res = NULL;
		*i = 0;
		while (data->files->file[*i])
			quote_checker(data->files->file, res, i, 0);
		if (data->files->heredoc_fd != -1)
			data->files->file = ft_strdup(*res);
		*res = NULL;
	}
	else if (!ft_strncmp(data->files->redirection, "<<", 3)
		&& data->files->file)
	{
		data->files->heredoc_fd = open_heredoc(data->files->file);
		if (data->files->heredoc_fd == -1)
			return (0);
	}
	return (1);
}
int ft_expand_file(t_data *cmd_list)
{
    t_data  *curr_d;
    t_files *curr_f;
    int i;

    curr_d = cmd_list;
    while (curr_d)
    {
        curr_f = curr_d->files;
        while (curr_f)
        {
            i = 0;
            if (ft_herdoc(curr_d, &i) == 0)
                return (0);
            curr_f = curr_f->next;
        }
        curr_d = curr_d->next;
    }
    return (1);
}