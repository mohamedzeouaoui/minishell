/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:50:07 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/12/06 16:50:12 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void pwd_update(char *path)
{
    if (serch_in_env("PWD") != NULL)
    {
        free(serch_in_env("PWD")->value);
        serch_in_env("PWD")->value = ft_strdup_normal(path);
    }
    // if ()
    // {
        // we need some condition to update the pwd in the shell state
    // }
    free(path);
    free(get_shell_state()->pwd);
    get_shell_state()->pwd = getcwd(NULL, 0);
    return ;
}

int cd_to_path(t_data *data)
{
    char *path;

    path = getcwd(NULL, 0);
    if (path == NULL && chdir(data->args[1])== -1)
    {
        if(get_shell_state()->pwd != NULL)
            print_errore_mix("minishell: cd: ",data->args[1],
            "No such file or directory\n", -1);
        else
            print_errore_mix("chdir: error retrieving current directory: ",
				"getcwd: cannot access parent directories: ",
				"No such file or directory\n", -1);
        return (1);
    }
    else if (data->args[1][0] != '\0' && chdir(data->args[1]) == -1)
    {
        free(path);
        print_errore("minishell: cd: ");
        perror(data->args[1]);
    }
    //update pwd;
    pwd_update(path);
    return (0);
}


int home_cd(void)
{
    char *home;
    
    if((serch_in_env("HOME")) == NULL || (serch_in_env("HOME")->value) == NULL)
    {
        print_errore("minishell: cd: HOME not set\n");
        return (1);
    }
    home = getcwd(NULL, 0);
    if (home == NULL && chdir(serch_in_env("HOME")->value) == -1)
    {
        print_errore_mix("minishell: cd: ", serch_in_env("HOME")->value,
			": No such file or directory\n", -1);
        return (1);
    }
    else if (chdir(serch_in_env("HOME")->value) == -1 && serch_in_env("HOME")->value != NULL)
    {
        free(home);
        print_errore("minishell: cd: ");
        perror(serch_in_env("HOME")->value);
        return (1);
    }
    //updtate pwd;
    pwd_update(home);
    return (0);
}


int ft_cd(t_data *data)
{
    int i;

    if (data->args[1] == NULL)
    {
        i = home_cd();
        return (i);
    }
    else if (data->args[2] != NULL)
    {
        print_errore("minishell: cd: too many arguments\n");
        return (1);   
    }
    else
    {
        i = cd_to_path(data);
        return (i);
    }
    return (0);
}
