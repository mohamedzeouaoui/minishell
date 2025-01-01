/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 02:14:50 by asodor            #+#    #+#             */
/*   Updated: 2024/11/19 18:02:41 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>
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
        if (strcmp(str, reds[i]) == 0)
            return (1);
    }
    return (0);
}
static t_files *make_new(char *operator, char *filename)
{
    t_files *new_file;

    new_file = (t_files *)mallocc(sizeof(t_files));
    new_file->redirection = ft_strdup(operator);
    new_file->file = ft_strdup(filename);
    new_file->next = NULL;
    return (new_file);
}
static t_files *add_last(t_files **files, t_files *new_file)
{
    t_files *current;

    if (!*files)
        return (new_file);

    current = *files;
    while (current->next)
        current = current->next;
    current->next = new_file;
    return (*files);
}
/*
** Process a single redirection operator and its argument
** Updates index to skip processed tokens
** Returns: 1 if redirection was processed, 0 if not
*/
static int process_redirection(t_data *cmd, char **args, int *index)
{
    t_files  *new_file;
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

static char **ft_new_args(char **args)
{
    int i;
    char **new_args;

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