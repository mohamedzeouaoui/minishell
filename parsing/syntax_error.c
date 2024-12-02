/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:38:01 by asodor            #+#    #+#             */
/*   Updated: 2024/12/01 11:44:47 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*ft_red_error(t_data *cmd_list)
{
	t_data			*curr;
	t_files	*tmp;

	curr = cmd_list;
	while (curr)
	{
		tmp = curr->files;
		while (tmp)
		{
			if (tmp->file == NULL)
			{
				//get_specials()->exit_status = 2;
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
	//t_spec	*svars;

	curr = cmd_list;
	//svars = get_specials();
	while (curr)
	{
		if (curr->next != NULL)
		{
			if ((curr->args == NULL && curr->files == NULL)
				|| (curr->next->args == NULL && curr->next->files == NULL))
			{
				//svars->exit_status = 2;
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
	//t_spec	*svars;

	//svars = get_specials();
	// if (!ft_her_error(cmd_list))
	// 	return (NULL);
	if (!ft_red_error(cmd_list) || !ft_pipe_error(cmd_list))
	{
		//expand_file(cmd_list);
		//svars->exit_status = 2;
		return (NULL);
	}
	//if (!expand_file(cmd_list))
		//return (NULL);
	//ft_expand(cmd_list);
	return (cmd_list);
}


