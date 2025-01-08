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

void sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    get_shell_state()->exit_status =(128 + signum);
}

void sig_handler_child(int signum)
{
    if (signum == SIGINT)
        write(1, "\n", 1);
    else if (signum == SIGQUIT)
        write(1, "Quit (core dumped)\n", 19);
}

void setup_signals(void)
{
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
}
// void heredoc_signal(int signum)
// {
//     signal(SIGINT, SIG_DFL);
//     signal(SIGQUIT, SIG_IGN);
//     if (signum == SIGINT)
//         exit(130);
//     // exit(130);
// }

void child_process()
{
    signal(SIGINT, sig_handler_child);
    signal(SIGQUIT, sig_handler_child);
    // Rest of your child process code
}
