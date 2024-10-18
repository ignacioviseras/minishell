/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:48:19 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/18 14:17:37 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	ft_lstlastchar(t_token *lst)
{
	t_token	*aux;
	int		i;

	aux = lst;
	i = 0;
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->value[i + 1] != '\0')
		i++;
	return (aux->value[i]);
}

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && input[*i] == ' ')
		(*i)++;
}

int ft_charcmp(char c1, char c2)
{
    return (c1 - c2);
}