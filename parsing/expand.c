/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:26:03 by asodor            #+#    #+#             */
/*   Updated: 2024/12/01 13:03:07 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *export_handle(char *arg)
{
    char *result;
    int equal_pos;
    char *value_part;

    // No need to process if there's no equals sign
    if (!ft_strchr(arg, '=', &equal_pos))
        return arg;

    // Split string into "var=" and "value" parts
    result = ft_strnjoin(NULL, arg, equal_pos + 1);  // Get "var=" part
    value_part = arg + equal_pos;                     // Point to value after '='

    // Only quote the value if:
    // 1. The value contains a $ variable
    // 2. The variable name doesn't contain a $ variable
    if (!ft_strchr(result, '$', NULL) && ft_strchr(value_part, '$', NULL))
    {
        result = ft_strnjoin(result, quotes_adder(value_part + 1), 0);
        return result;
    }

    return arg;
} 

void ft_expand(t_data *cmd_list)
{
    t_data *curr;
    
    curr = cmd_list;
    while (curr)
    {
        int i = 0;
        while (curr->args && curr->args[i])
        {
            if (!ft_strncmp("export", curr->args[0], ft_strlen(curr->args[0])))
                curr->args[i] = export_handle(curr->args[i]);
            char **res = catch_expnad(curr->args[i]);
            if (res && *res)
            {
                int j = 0;
                char **args_res = NULL;
                while (res[j])
                    args_res = ft_tablejoin(args_res, res[j++]);
                curr->args = args_res;
            }
            i++;
        }
        curr = curr->next;
    }
}

char	*export_handle(char *arg)
{
	char	*res;
	int		i_eq;

	res = NULL;
	i_eq = 0;
	if (ft_strchr(arg, '=', &i_eq))
	{
		res = ft_strnjoin(res, arg, (i_eq + 1));
		if (!ft_strchr(res, '$', NULL) && ft_strchr(arg + i_eq, '$', NULL))
		{
			res = ft_strnjoin(res, quotes_adder(arg + (i_eq + 1)), 0);
			return (res);
		}
	}
	return (arg);
}


void	expand(t_data *data)
{
	int		i;
	int		j;
	char	**res;
	char	**args_res;

	while (data)
	{
		i = -1;
		res = NULL;
		args_res = NULL;
		while (data->args && data->args[++i])
		{
			if (!ft_strncmp("export", data->args[0], ft_strlen(data->args[0])))
				data->args[i] = export_handle(data->args[i]);
			res = catch_expnad(data->args[i]);
			if (res && *res)
			{
				j = 0;
				while (res[j])
					args_res = ft_tablejoin(args_res, res[j++]);
			}
		}
		data->args = args_res;
		data = data->next;
	}
}
