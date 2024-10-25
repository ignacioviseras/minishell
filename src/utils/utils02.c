/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:48:19 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/25 14:03:43 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	index;
	char			*substr;
	char			*schar;

	index = 0;
	if (start >= ft_strlen(s) || !*s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	schar = (char *)s;
	while (s[index] || !*s)
	{
		if (index == start)
		{
			ft_strlcpy(substr, schar + index, len + 1);
			return (substr);
		}
		index++;
	}
	return (NULL);
}

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

int ft_charcmp(char c1, char c2)
{
    return (c1 - c2);
}

void	skip_spaces(char **input)
{
	while (*input && **input == ' ')
		(*input)++;
}
