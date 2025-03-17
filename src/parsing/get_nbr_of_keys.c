/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nbr_of_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:01:43 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/17 16:22:02 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_nbr_of_keys(char *str)
{
	int	keys;

	keys = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		else if (*str == '"')
		{
			str++;
			while (*str != '"')
			{
				if (*str == '$')
					keys++;
				str++;
			}
		}
		else if (*str == '$')
			keys++;
		str++;
	}
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
