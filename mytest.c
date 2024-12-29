#include "minishell.h"
#include <stdio.h>


t_shell *get_shell_state(void)
{
    static t_shell	s;
    return (&s);
} 
// int main(void)
// {
//     t_data    *cmd_list;
//     char        *input;

//     while (1)
//     {
//         // Get input from user
//         input = readline("minishell-test> ");
//         if (!input)
//             break;

//         // Add input to history
//         //add_history(input);

//         // Parse the input into command list
//         cmd_list = tokenize_input(input);
        
//         // Print command structure
//         t_data *current = cmd_list;
//         if (!current)
//             printf("errrrr/n");
//         int cmd_num = 0;
//                 while (current)
//                 {
//                     printf("\n=== Command %d ===\n", ++cmd_num);
                    
//                     // Print arguments
//                     printf("Arguments: ");
//                     if (current->args)
//                     {
//                         for (int i = 0; current->args[i]; i++)
//                             printf("[%s] ", current->args[i]);
//                         if (current->files){
//                             printf("\n");
//                             for (t_files *file = current->files; file; file = file->next)
//                             {
//                                 printf("\tRedirection: %s\n", file->redirection);
//                                 printf("\tFile: %s\n", file->file);
//                             }
//                         }
//                     }
//                     printf("\n");
                    


// 			// ft_exec(current, ft_lstsize(current));
                    
//                 //     current = current->next;
//                 }
        
//         // Clean up
//         //free_command_list(cmd_list);
//         free(input);
//     }
    
//     return (0);
// }

int main(int ac, char **av, char **env)
{
    t_data *cmd_list;
    char *input;

    t_shell *shell;
    
    shell = get_shell_state();
    shell->exit_status = 0;
    ft_parse_env(env, shell);
    
    
    while (1)
    {
        // Get input from user
        input = readline("minishell-test> ");
        if (!input)
            break;

        // Add input to history
        add_history(input);

        // Parse the input into command list
        cmd_list = tokenize_input(input);
        
        // Print command structure
        t_data *current = cmd_list;
        if (!current)
            printf("Error: Command list is empty\n");
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
                printf("\n");
            }

            // Print file redirections
            if (current->files)
            {
                for (t_files *file = current->files; file; file = file->next)
                {
                    printf("\tRedirection: %s\n", file->redirection);
                    printf("\tFile: %s\n", file->file);
                }
            }

            // Execute the command
            
            current = current->next;
        }
        
        // Clean up
        //free_command_list(cmd_list);
        free(input);
    }
    
    return 0;
}