/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:22:53 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/01/10 20:34:55 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_run_path_not_commande(char *path, t_data *data)
{
	char	*new_path;

	if (path[0] == '/')
		new_path = path;
	else
		new_path = ft_strjoin("./", path, ft_strlen(path));
	if (access(new_path, F_OK) == 0)
	{
		check_dirctory(new_path);
		if (access(new_path, X_OK) == 0)
		{
			if (execve(new_path, data->args, env_lst_to_tab()) == -1)
				print_errore_mix(" permission denied\n", NULL, NULL, 127);
			exit(get_shell_state()->exit_status);
		}
		else
			print_errore_mix("minishell: ", path, " permission denied\n", 126);
	}
	else
		print_errore_mix("minishell: ", path, ": No such file or directory\n",
			127);
}

void	exe_ve_abd_chech_dir(t_data *data, char *new_path)
{
	check_dirctory(new_path);
	if (execve(new_path, data->args, env_lst_to_tab()) == -1)
		print_errore_mix("minishell: ", " permission denied\n", NULL, 127);
	exit(get_shell_state()->exit_status);
}

void	check_in_env_path_cmd(char *cmd, t_data *data)
{
	char	**path_env;
	int		i;
	char	*new_path;

	if (search_in_env("PATH") == NULL || search_in_env("PATH")->value == NULL
		|| search_in_env("PATH")->value[0] == '\0')
	{
		print_errore_mix("minishell: ", cmd, " command not found\n", 127);
		return ;
	}
	path_env = ft_split(search_in_env("PATH")->value, ':');
	i = -1;
	while (path_env[++i])
	{
		new_path = ft_strjoin(ft_strjoin(path_env[i], "/", 0), cmd,
				ft_strlen(cmd));
		if (access(new_path, F_OK) == 0)
			exe_ve_abd_chech_dir(data, new_path);
		free(path_env[i]);
		free(new_path);
	}
	get_shell_state()->exit_status = 127;
	print_errore_mix("minishell: ", cmd, " command not found\n", 127);
}

bool	check_slash_in_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

void	command_not_found(t_data *data)
{
	if (ft_strncmp(data->args[0], "..", 3) == 0)
		print_errore_mix("minishell: ", data->args[0], " command not found\n",
			127);
	else if (ft_strncmp(data->args[0], ".", 2) == 0)
		print_errore_mix("minishell: ", ".: filename argument required\n",
			".: usage: . filename [arguments]\n", 2);
	else if (ft_strncmp(data->args[0], "", 1) == 0)
		print_errore_mix("minishell: ", data->args[0], " command not found\n",
			127);
}
