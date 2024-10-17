/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:48:19 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/17 17:03:55 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strchr(const char *s, int c)
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

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen((char *)s))
	{
		sub = malloc (1 * sizeof(char));
		if (!(sub))
			return (NULL);
		sub[i] = '\0';
		return (sub);
	}
	sub = (char *)malloc(ft_min(ft_strlen(s) - start, len) + 1);
	if (sub == NULL)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

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
