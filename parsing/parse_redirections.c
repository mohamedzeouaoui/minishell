/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 02:14:50 by asodor            #+#    #+#             */
/*   Updated: 2025/01/11 02:05:55 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

/*
** Check if string is a redirection operator
** Returns: 1 if redirection, 0 if not
*/

static int	is_redirection(const char *str)
{
	int		i;
	char	*reds[5];

	reds[0] = "<";
	reds[1] = ">";
	reds[2] = ">>";
	reds[3] = "<<";
	reds[4] = NULL;
	i = 0;
	if (!str)
		return (0);
	while (reds[i] != NULL)
	{
		if (ft_strncmp(str, reds[i], ft_strlen(reds[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

static t_files	*make_new(char *operator, char *filename)
{
	t_files	*new_file;

	new_file = (t_files *)mallocc(sizeof(t_files));
	new_file->redirection = ft_strdup(operator);
	new_file->file = ft_strdup(filename);
	new_file->next = NULL;
	return (new_file);
}

/*
** Process a single redirection operator and its argument
** Updates index to skip processed tokens
** Returns: 1 if redirection was processed, 0 if not
*/

static int	process_redirection(t_data *cmd, char **args, int *index)
{
	t_files	*new_file;
	char	*operator;
	char	*filename;

	operator = args[*index];
	if (!is_redirection(operator))
		return (0);
	filename = NULL;
	if (args[*index + 1] && !is_redirection(args[*index + 1]))
	{
		filename = args[*index + 1];
		*index += 2;
	}
	else
		*index += 1;
	new_file = make_new(operator, filename);
	cmd->files = add_last(&cmd->files, new_file);
	return (1);
}

static char	**ft_new_args(char **args)
{
	int		i;
	char	**new_args;

	i = 0;
	new_args = NULL;
	while (args && args[i])
	{
		new_args = ft_cmd_join(new_args, args[i]);
		i++;
	}
	return (new_args);
}

/*
** Process all redirections in a command
** Separates redirections from command arguments
*/

void	parse_redirections(t_data *cmd_list)
{
	int		i;
	char	**new_args;
	t_data	*current;

	current = cmd_list;
	while (current)
	{
		i = 0;
		new_args = NULL;
		while (current->args && current->args[i])
		{
			if (!process_redirection(current, current->args, &i))
			{
				new_args = ft_cmd_join(new_args, current->args[i]);
				i++;
			}
		}
		current->args = ft_new_args(new_args);
		current = current->next;
	}
}
