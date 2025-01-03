/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:38:01 by asodor            #+#    #+#             */
/*   Updated: 2025/01/04 00:29:08 by asodor           ###   ########.fr       */
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

t_data	*ft_errors(t_data *cmd_list)
{
	// if (!ft_her_error(cmd_list))
	// 	return (NULL);
	if (!ft_red_error(cmd_list) || !ft_pipe_error(cmd_list))
	{
		//check for file!!!
		get_shell_state()->exit_status = 2;
		return (NULL);
	}
	return (cmd_list);
}


