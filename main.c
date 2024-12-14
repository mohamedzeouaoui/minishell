/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:14:23 by asodor            #+#    #+#             */
/*   Updated: 2024/12/05 18:24:31 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell *get_shell_state(void)
{
    static t_shell	s;
    return (&s);
} 

void	minishell(void)
{
	char	*str;
	t_data	*tmp;

	str = NULL;
	while (1)
	{
		// signals
		str = readline("minishell $> ");
		tokenize_input(str); // <-------- I'm Here
		// add history
		free(str);
		// if (tmp != NULL)
		// 	ft_exec(tmp, ft_lstsize(tmp));
		// free
	}
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_shell *shell;
    
    shell = get_shell_state();
    shell->exit_status = 0;
    ft_parse_env(env, shell);
    minishell();
    return 0;
}


