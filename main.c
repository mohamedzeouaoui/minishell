/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:56:19 by asodor            #+#    #+#             */
/*   Updated: 2024/11/23 01:02:15 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	machiBash(void)
// {
// 	char	*str;
// 	//t_data	*tmp;

// 	str = NULL;
// 	while (1)
// 	{
// 		// signals
// 		str = readline("minishell $> ");
// 		tokenize_input(str); // <-------- I'm Here
// 		// add history
// 		free(str);
// 		//if (tmp != NULL)
// 		//	ft_exec(tmp, ft_lstsize(tmp));
// 		// free
// 	}
// }

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	machiBash();
// 	return (0);
// }

#include "minishell.h"
#include <stdio.h>

int main(int ac, char **av, char **env)
{
    t_data    *cmd_list;
    char        *input;
    (void)av;
    (void)ac;
    (void)env;

    while (1)
    {
        // Get input from user
        input = readline("minishell-test> ");
        if (!input)
            break;

        // Add input to history
        //add_history(input);

        // Parse the input into command list
        cmd_list = tokenize_input(input);
        
        // Print command structure
        t_data *current = cmd_list;
        if (!current)
            printf("errrrr/n");
        int cmd_num = 0;
                while (current)
                {
                    printf("\n=== Command %d ===\n", ++cmd_num);
                    
                    // Print arguments
                    printf("Arguments: ");
                    if (current->args)
                    {
                        for (int i = 0; current->args[i]; i++)
                            printf("[%s] ", current->args[i]);
                        if (current->files){
                            printf("\n");
                            for (t_files *file = current->files; file; file = file->next)
                            {
                                printf("\tRedirection: %s\n", file->redirection);
                                printf("\tFile: %s\n", file->file);
                            }
                        }
                    }
                    printf("\n");
                    
                    
                    current = current->next;
                }
        
        // Clean up
        //free_command_list(cmd_list);
        free(input);
    }
    
    return (0);
}
