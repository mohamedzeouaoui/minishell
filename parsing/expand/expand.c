/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:26:03 by asodor            #+#    #+#             */
/*   Updated: 2025/01/11 02:41:46 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_init_helper(t_helper *helper, char *str)
{
	int	len;

	len = ft_strlen(str);
	helper->i = 0;
	helper->j = 0;
	helper->quote = 0;
	helper->from_env = 0;
	helper->result = mallocc(sizeof(char) * (len * 100));
	if (!helper->result)
		return ;
}

char	**ft_handle_expansions(char *str, int flag)
{
	t_helper	h;
	char		**result_arr;

	result_arr = NULL;
	ft_init_helper(&h, str);
	ft_handle_quotes(&h, str);
	h.result[h.j] = '\0';
	if (ft_strchr(str, '$') && flag == 1 && !ft_strchr(str, ' '))
		result_arr = ft_split(h.result, ' ');
	else
	{
		result_arr = mallocc(2 * sizeof(char *));
		result_arr[0] = h.result;
		result_arr[1] = NULL;
	}
	return (result_arr);
}

void	ft_expand_args(t_data *current)
{
	int		i;
	int		j;
	char	**expanded_args;
	char	**new_args;

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
	}
	current->args = new_args;
}

void	ft_expand_files(t_files *files)
{
	t_files	*current;
	char	**new_file;

	current = files;
	while (current && current->file)
	{
		if (!ft_strncmp(current->redirection, "<<", 3))
			new_file = ft_remove_quotes(current->file);
		else
			new_file = ft_handle_expansions(current->file, 0);
		if (new_file && *new_file)
		{
			free(current->file);
			current->file = new_file[0];
			free(new_file);
		}
		current = current->next;
	}
}

void	ft_expand(t_data *cmd_list)
{
	t_data	*current;

	current = cmd_list;
	while (current)
	{
		ft_expand_args(current);
		ft_expand_files(current->files);
		current = current->next;
	}
}
