/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:56:19 by asodor            #+#    #+#             */
/*   Updated: 2025/01/11 04:31:51 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*get_shell_state(void)
{
	static t_shell	s;

	return (&s);
}

int	main(int ac, char **av, char **env)
{
	t_data	*cmd_list;
	t_data	*current;
	char	*input;
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = get_shell_state();
	get_shell_state()->herdoc = -1;
	shell->exit_status = 0;
	ft_parse_env(env, shell);
	while (1)
	{
		signal_cases_handel(0);
		input = readline("minishell:> ");
		if (!input)
			break ;
		add_history(input);
		cmd_list = tokenize_input(input);
		current = cmd_list;
		if (current)
			ft_exec(current, ft_lstsize(current));
		free(input);
	}
	return (0);
}
