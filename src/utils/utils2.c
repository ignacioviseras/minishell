/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:48:19 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/24 01:09:30 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_charseach(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == s[i])
		return (i);
	return (0);
}

char	ft_lstlastchar(t_token *lst)
{
	t_token	*aux;
	int		i;

	aux = lst;
	i = 0;
	while (aux->next != NULL)
		aux = aux->next;
	while (aux->cmd_args[i + 1] != '\0')
		i++;
	return (aux->cmd_args[i]);
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
