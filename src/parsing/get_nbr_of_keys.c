/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbr_of_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:01:43 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/20 17:32:13 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*get_command(char *full_cmd)
{
	char	*cmd;
	int		i;

	i = 0;
	while (full_cmd[i] == ' ')
		i++;
	cmd = ft_substr(full_cmd, i, get_word_len(full_cmd, i));
	return (cmd);
}
