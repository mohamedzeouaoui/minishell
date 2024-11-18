/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 02:14:50 by asodor            #+#    #+#             */
/*   Updated: 2024/11/18 17:24:25 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Check if string is a redirection operator
** Returns: 1 if redirection, 0 if not
*/
static int is_redirection(const char *str)
{
    int i;
    char *reds[] = {"<", "<<", ">", ">>"};

    for (i = 0; i < 4; i++)
    {
        if (ft_strcmp(str, reds[i]) == 0)
            return (1);
    }
    return (0);
}

/*
** Process a single redirection operator and its argument
** Updates index to skip processed tokens
** Returns: 1 if redirection was processed, 0 if not
*/
static int process_redirection(t_data *cmd, char **args, int *index)
{
    t_file  *new_file;
    char    *operator;
    char    *filename;

    operator = args[*index];
    if (!is_redirection(operator))
        return (0);

    // Check if next argument exists and is not a redirection
    filename = NULL;
    if (args[*index + 1] && !is_redirection(args[*index + 1]))
    {
        filename = args[*index + 1];
        *index += 2;  // Skip both operator and filename
    }
    else
    {
        *index += 1;  // Skip only operator
    }

    // Add to files list
    new_file = make_new(operator, filename);
    cmd->files = add_last(&cmd->files, new_file);

    return (1);
}

/*
** Process all redirections in a command
** Separates redirections from command arguments
*/
void parse_redirections(t_data *cmd_list)
{
    int     i;
    char    **new_args;
    t_data  *current;

    current = cmd_list;
    while (current)
    {
        i = 0;
        new_args = NULL;

        // Process each argument in the command
        while (current->args && current->args[i])
        {
            if (!process_redirection(current, current->args, &i))
            {
                // Not a redirection, add to new arguments
                new_args = ft_cmd_join(new_args, current->args[i]);
                i++;
            }
        }

        // Update command arguments (without redirections)
        current->args = ft_new_args(new_args);
        current = current->next;
    }
}