/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:02:54 by asodor            #+#    #+#             */
/*   Updated: 2024/10/27 06:30:17 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_files
{
	char				*redirection;
	char				*file;
	int					heredoc_fd; //<-------
	struct s_files	*next;
}						t_files;

typedef struct s_data
{
	char			**args;//--> cmd args ex: "ls" "-la"
	t_files     	*files;//
	struct s_data	*next;// next node
}						t_data;

typedef struct s_stack
{
	void	*ptr;
	struct	s_stack	*next;
}						t_stack;

//parsing
t_data *tokenize_input(char *input);

//utils
t_data  *ft_lstnew(void);

#endif