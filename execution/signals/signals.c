/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:58:15 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/01/07 19:58:17 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

__sighandler_t	ft_signal(int _sig, __sighandler_t _handler)
{
	__sighandler_t	ret;

	ret = signal(_sig, _handler);
	if (ret == SIG_ERR)
	{
		perror("minishell");
		exit(1);
	}
	return (ret);
}

void	signal_handler(int sig)
{
	get_shell_state()->exit_status = 128 + sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	ft_signal(sig, signal_handler);
}

void	signal_cases_handel(int cas)
{
	if (cas == 0)
	{
        get_shell_state()->exit_status = 130;
		ft_signal(SIGINT, signal_handler);
		ft_signal(SIGQUIT, SIG_IGN);
	}
	else if (cas == 1)
	{
        get_shell_state()->exit_status = 130;
		ft_signal(SIGINT, SIG_IGN);
		ft_signal(SIGQUIT, SIG_IGN);
	}
    else if (cas == 2)
    {
        signal(SIGINT, SIG_DFL);
    }
}



