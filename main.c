/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:56:19 by asodor            #+#    #+#             */
/*   Updated: 2024/10/26 05:57:02 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    machiBash(){
    char    *str;
    t_data   *tmp;

    str = NULL;
    while (1)
    {
        //signals
        str = readline("minishell $> ");
        tmp = tokenize_input(str);// <-------- I'm Here
        //add history
        free(str);
        if (tmp != NULL)
        ft_exec(tmp, ft_lstsize(tmp));
        //free
    }
}



int main(int ac, char **av, char **env) {
    (void)ac;
    (void)av;
    machiBash();
    return 0;
}
