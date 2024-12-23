/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:00:38 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/06 17:00:43 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void command_not_found(t_data *data)
{
    if(data->args[0] == "..")
        print_errore_mix(data->args[0], " command not found", NULL, 127);
    else if(data->args[0] == ".")
        print_errore_mix(data->args[0], " command not found", NULL, 2);
    else if(data->args[0] == "")
        print_errore_mix(data->args[0], " command not found", NULL, 127);
}
bool check_slash_in_path(char *path)
{
    int i;

    i = 0;
    while (path[i])
    {
        if (path[i] == '/')
            return (true);
        i++;
    }
    return (false);
}

int check_dirctory(char *path)
{
    struct stat sb;

    if (stat(path, &sb) == -1)
    {
        print_errore_mix("minishell: ", path, " no such file or directory", 127);
        return (1);
    }
    if (S_ISDIR(sb.st_mode))
    {
        print_errore_mix("minishell: ", path, " is a directory", 126);
        return (1);
    }
    return (0);
}

void check_run_path_not_commande(char *path, t_data *data)
{
    char *new_path;

    if (path[0] == '/')
        new_path = path;
    else
        new_path = ft_strjoin("./", path, ft_strlen(path));    
    if (access( new_path, F_OK) == 0)
    {
        check_dirctory(new_path);
        if (access(new_path, X_OK) == 0)
        {
            if (execve(new_path, data->args, env_lst_to_tab()) == -1)
                print_errore_mix(" permission denied", NULL, NULL, 127);
        }
        else
            print_errore_mix("minishell: ", path, " permission denied", 126);
    }
    else
        print_errore_mix("minishell: ", path, ": No such file or directory\n" ,127);
}

void check_in_env_path_cmd(char *cmd, t_data *data)
{
    char **path_env;
    int i;
    char *new_path;

    if (serch_in_env("PATH") == NULL || serch_in_env("PATH")->value == NULL || serch_in_env("PATH")->value[0] == '\0')
    {
        print_errore_mix("minishell: ", cmd, " command not found", 127);
        return ;
    }    
    path_env = ft_split(serch_in_env("PATH")->value, ':');
    i = 0;
    while (path_env[i])
    {
        new_path = ft_strjoin(ft_strjoin(path_env[i], "/", 0), cmd, ft_strlen(cmd));
        if (access(new_path, F_OK) == 0)
        {
            check_dirctory(new_path);
            if (execve(new_path, data->args, env_lst_to_tab()) == -1)
                print_errore_mix(" permission denied", NULL, NULL, 127);
        }
        free(path_env[i]);
        //ft_free(new_path);
        i++;
    }
    print_errore_mix("minishell: ", cmd, " command not found", 127);
}


int command_execution(t_data *data, int size)
{

    command_not_found(data);


    if (check_slash_in_path(data->args[0]) == true)
        check_run_path_not_commande(data->args[0], data);
    else
        check_in_env_path_cmd(data->args[0], data);
    exit(get_shell_state()->exit_status); // should be exit with ft_exit_clean !!!!
    //ft_exit_clean(get_shell_state()->exit_status);
    return (0);
}

void run_command_in_child_process(t_data *data, int *id_child, int size, int *i)
{
    // int fd_pipe[2];
    int fd_stdout;

    // if (size > 1 && *i < size - 1)
    // {
    //     if (pipe(fd_pipe) == -1)
    //         print_errore_exit("pipe_error", 1);
    // }
   int pid = fork();
    // if ((id_child[*i] = fork()) == -1)
    //     print_errore_exit("fork_error", 1);
    // printf("parent\n,%d\n", id_child[*i]);
    // close(fd_stdin);
    // printf("child\n");
    if (pid == 0)
    {
        if (check_built(data, 0) == 0)
        {

            command_execution(data, size);
        }
        // if()ls  | ls | ls
        // {
        //     // hamdel file
        // }       
        exit(get_shell_state()->exit_status);
    }
    
    // waitpid(id_child[*i], &get_shell_state()->exit_status, 0);
}

void    ft_exec(t_data *data, int size)
{
    int i;
    int *id_child;
    
    // t_shell *shell;

    if (check_built(data, 1) == 1 && size == 1)
        return ;
    get_shell_state()->exit_status = 0;
    // if(command_execution(data, size) == 1 && size == 1)
    //     return ;
    i = 0;
    while (i < size && data != NULL)
    {
        run_command_in_child_process(data, id_child, size, &i);
        i++;
    }
    // wait(NULL);
    int status;
    waitpid(-1, &status, 0);
    printf("status: %d\n", status);
    // while (i < size)
    // {
    //     printf("wait:%d\n", id_child[i]);
    //     waitpid(id_child[i], &get_shell_state()->exit_status, 0);
    //     i++;
    // }
}
