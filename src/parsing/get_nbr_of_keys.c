/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbr_of_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:01:43 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/22 17:50:35 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* void	update_nbr_of_keys(char **str, int *keys)
{
	if (**str == '\'')
	{
		(*str)++;
		while (**str && **str != '\'')
			(*str)++;
		(*str)++;
	}
	else if (**str == '"')
	{
		(*str)++;
		while (**str && **str != '"')
		{
			if (**str == '$')
				(*keys)++;
			(*str)++;
		}
		(*str)++;
	}
	else if (**str == '$' && \
	(is_alpha(*(*str + 1)) || *(*str + 1) == '_' || *(*str + 1) == '?'))
	{
		(*str)++;
		(*keys)++;
	}
	else
		(*str)++;
} */

void	update_nbr_of_keys(char **str, int *keys)
{
	char	quote;

	if (**str == '\'' || **str == '"')
	{
		quote = *(*str)++;
		while (**str && **str != quote)
		{
			if (quote == '"' && **str == '$')
				(*keys)++;
			(*str)++;
		}
		if (**str)
			(*str)++;
	}
	else if (**str == '$' && (is_alpha(*(*str + 1)) || \
			*(*str + 1) == '_' || *(*str + 1) == '?'))
	{
		(*str)++;
		(*keys)++;
	}
	else
		(*str)++;
}

int	get_nbr_of_keys(char *str)
{
	int	keys;

	keys = 0;
	while (*str)
		update_nbr_of_keys(&str, &keys);
	return (keys);
}
