/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:00:38 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/01/11 04:35:27 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_execution(t_data *data, int size)
{
	(void)size;
	if (data == NULL || data->args == NULL)
		return (0);
	command_not_found(data);
	if (check_slash_in_path(data->args[0]) == true)
		check_run_path_not_commande(data->args[0], data);
	else
		check_in_env_path_cmd(data->args[0], data);
	exit(get_shell_state()->exit_status);
	return (0);
}

void	close_fd_in_child(int *fd_stdout_stored, int fd_pipe[2], int size,
		int i)
{
	if (size > 1 && i != size - 1)
		close(fd_pipe[P_INP]);
	if (*fd_stdout_stored != -1)
		close(*fd_stdout_stored);
	(*fd_stdout_stored) = fd_pipe[P_OUTP];
}

void	run_command_in_child_process(t_data *data, t_variables *var, int size)
{
	int	fd_pipe[2];

	if (size > 1 && var->i != size - 1)
	{
		if (pipe(fd_pipe) == -1)
			print_errore_exit("pipe_error\n", 1);
	}
	var->id_child[var->i] = fork();
	if (var->id_child[var->i] == -1)
		print_errore_exit("fork_error\n", 1);
	if (var->i == size - 1 && var->id_child[var->i] != 0)
		(var->last_process_id) = var->id_child[var->i];
	if (var->id_child[var->i] == 0)
	{
		signal_cases_handel(2);
		files_pipe(fd_pipe, (var->fd_stdout_stored), size, var->i);
		if (data->files != NULL)
			file_redirection(data->files, 0);
		if (check_built(data, 0) == 0)
			command_execution(data, size);
		exit(get_shell_state()->exit_status);
	}
	signal_cases_handel(1);
	close_fd_in_child(&var->fd_stdout_stored, fd_pipe, size, var->i);
}

void	ft_exec(t_data *data, int size)
{
	t_variables	var;

	var.i = 0;
	var.fd_stdout_stored = -1;
	var.last_process_id = -1;
	var.status = 0;
	var.pid = 0;
	if (size == 1 && check_built(data, 1) == 1)
		return ;
	var.id_child = (int *)mallocc(sizeof(int) * size);
	get_shell_state()->exit_status = 0;
	while (var.i < size)
	{
		run_command_in_child_process(data, &var, size);
		data = data->next;
		var.i++;
	}
	var.i = -1;
	assert(var.last_process_id != -1);
	while (++var.i < size)
	{
		var.pid = waitpid(-1, &var.status, 0);
		if (var.pid == var.last_process_id)
			get_shell_state()->exit_status = WEXITSTATUS(var.status);
	}
}
