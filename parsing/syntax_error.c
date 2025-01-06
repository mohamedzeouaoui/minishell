/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:38:01 by asodor            #+#    #+#             */
/*   Updated: 2025/01/06 17:07:45 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*ft_red_error(t_data *cmd_list)
{
	t_data			*curr;
	t_files	*tmp;
	t_shell		*shell;
	
	shell = get_shell_state();
	curr = cmd_list;
	while (curr)
	{
		tmp = curr->files;
		while (tmp)
		{
			if (tmp->file == NULL)
			{
				shell->exit_status = 2;
				ft_print_err1("syntax error near unexpected token ",
					tmp->redirection, "\n", -1);
				return (NULL);
			}
			tmp = tmp->next;
		}
		curr = curr->next;
	}
	return (cmd_list);
}

t_data	*ft_pipe_error(t_data *cmd_list)
{
	t_data	*curr;

	curr = cmd_list;
	while (curr)
	{
		if (curr->next != NULL)
		{
			if ((curr->args == NULL && curr->files == NULL)
				|| (curr->next->args == NULL && curr->next->files == NULL))
			{
				get_shell_state()->exit_status = 2;
				return (ft_print_err("syntax error near unexpected token `|'\n")
					, NULL);
			}
		}
		curr = curr->next;
	}
	return (cmd_list);
}

int ft_count_herdoc(t_data *cmd_list)
{
	t_data	*curr;
	t_files	*tmp;
	int		count;

	count = 0;
	curr = cmd_list;
	while (curr)
	{
		tmp = curr->files;
		while (tmp)
		{
			if (tmp->redirection && !ft_strncmp(tmp->redirection, "<<", 3))
				count++;
			tmp = tmp->next;
		}
		curr = curr->next;
	}
	return (count);
}

t_data	*ft_errors(t_data *cmd_list)
{
	int herdoc;

	herdoc = ft_count_herdoc(cmd_list);
	if (!ft_red_error(cmd_list) || !ft_pipe_error(cmd_list) || herdoc > 16)
	{
		ft_expand(cmd_list);
		get_shell_state()->exit_status = 2;
		if (herdoc > 16)
		{
			ft_print_err("bash: maximum here-document count exceeded");
			//exitiiiiiiiiiiiiiiiiiiiiiiiiit !!!
		}
		if (herdoc > 0)
			ft_heredoc(cmd_list);
		return (NULL);
	}
	return (cmd_list);
}


