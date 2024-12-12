/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils08.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:48:06 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/11 18:01:50 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' ||
	 c == '\v' || c == '\f' || c == '\r');
}

char *trim_sp(const char *str)
{

    if (!str)
        return NULL;
    size_t len = ft_strlen(str);
    while (len > 0 && ft_isspace((unsigned char)str[len - 1]))
	{
        len--;
    }
    char *result = (char *)malloc(len + 1);
    if (!result)
        return NULL;
    ft_strncpy(result, str, len);
    result[len] = '\0';
    return result;
}