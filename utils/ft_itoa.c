/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asodor <asodor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:23:21 by asodor            #+#    #+#             */
/*   Updated: 2025/01/10 18:59:57 by asodor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_itoa(int n)
{
    char *str;
    int len;
    int sign;
    int tmp;

    sign = (n < 0);
    len = 1 + sign;
    tmp = n;
    while (tmp /= 10)
        len++;
    str = mallocc(sizeof(char) * (len + 1));
    if (!str)
        return NULL;
    str[len] = '\0';
    if (sign)
        str[0] = '-';
    while (len-- > sign)
    {
        str[len] = n % 10 * (1 - 2 * sign) + '0';
        n /= 10;
    }
    return str;
}