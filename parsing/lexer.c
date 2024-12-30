/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:22:01 by asodor            #+#    #+#             */
/*   Updated: 2024/12/30 23:32:25 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Checks if character is part of a word/token
** Returns 1 if true, 0 if false
*/

int is_word_character(const char *str, int pos, char quote_status)
{
    if (!str[pos] || quote_status != '\0')
        return (0);
        
    if (ft_iswhitespace(str[pos]))
        return (0);
        
    return (str[pos] != '|' && str[pos] != '<' && str[pos] != '>');
}

/*
** Processes special characters and quoted strings
** Returns 1 if successful, 0 if quotes are unclosed
*/
int process_token(const char *str, int *start, int *end)
{
    char quote_char;

    quote_char = '\0';
    
    // Handle redirection operators
    if (str[*start] == '<' || str[*start] == '>')
    {
        *end = *start + 1;
        // Check for double redirections (>> or <<)
        if (str[*start + 1] && str[*start] == str[*start + 1])
            *end = *start + 2;
        return (1);
    }
    
    // Process word characters and quotes
    while (is_word_character(str, *end, quote_char))
    {
        if (str[*end] == '\"' || str[*end] == '\'')
        {
            quote_char = str[*end];
            (*end)++;
            
            // Find matching closing quote
            while (str[*end] && str[*end] != quote_char)
                (*end)++;
                
            if (!str[*end])  // Unclosed quote
                return (0);
                
            quote_char = '\0';
        }
        (*end)++;
    }
    return (1);
}

/*
** Initialize data structures for command processing
*/
void initialize_command_data(t_data **cmd_list, char ***arg_array)
{
    *cmd_list = ft_lstnew();
    *arg_array = (char **)mallocc(sizeof(char *));
    (*arg_array)[0] = NULL;
}

/*
** Process single command and its arguments
** Returns command data structure or NULL if error
*/
t_data *parse_command(char *str, int *pos, int start, int end)
{
    char    *token;
    t_data  *cmd_data;
    char    **arguments;

    initialize_command_data(&cmd_data, &arguments);
    
    while (str[start] && str[start] != '|')
    {
        // Skip whitespace
        while (str[start] && ft_iswhitespace(str[start]))
            start++;
            
        // Process command/argument tokens
        while (str[start] && str[start] != '|' && !ft_iswhitespace(str[start]))
        {
            end = start;
            if (!process_token(str, &start, &end))
                return (NULL);  // Quote error
                
            token = ft_substr(str, start, end - start);
            arguments = ft_cmd_join(arguments, token);
            start = end;
        }
    }
    
    // Move past pipe if present
    if (str[start] == '|')
        start++;
        
    *pos = start;
    cmd_data->args = arguments;
    return (cmd_data);
}

/*
** Main lexical analysis function
** Returns linked list of commands or NULL if error
*/
t_data *tokenize_input(char *input)
{
    int     curr_pos;
    t_data  *cmd_list;
    t_data  *new_cmd;
    t_shell *shell;
    
    curr_pos = 0;
    cmd_list = NULL;

    // Add space for consistent parsing
    if (input && input[0])
        input = ft_strjoin(input, " ", 1);

    // Process each command (separated by pipes)
    while (input[curr_pos])
    {
        new_cmd = parse_command(input, &curr_pos, curr_pos, 0);
        if (!new_cmd)
        {
            //get_specials()->exit_status = 2;
            //print_err("Syntax error: Unclosed quotes\n");
            return (NULL);
        }
        ft_lstadd_back(&cmd_list, new_cmd);
    }
    parse_redirections(cmd_list);
    // Final error checking and status setting
    if (cmd_list && !ft_errors(cmd_list))
        return (NULL);
    ft_expand(cmd_list);
    if (cmd_list)
    {
        shell = get_shell_state();
        shell->exit_status = 0;
        // need to set last argument
    }
    return (cmd_list);
}