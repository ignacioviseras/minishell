/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:08 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 17:21:07 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_option_n(char *str)
{
	int	i;
	int	result;

	i = 1;
	result = 1;
	if (str[0] != '-')
		result = 0;
	else
	{
		while (str[i] == 'n')
			i++;
		if (str[i] != '\0')
			result = 0;
	}
	return (result);
}

void	command_echo(t_token *tokens)
{
	int		no_newline;

	no_newline = 1;
	if (tokens->flags && tokens->flags[0] == '-' && tokens->flags[1] == 'n' && \
		(tokens->flags[2] == ' ' || tokens->flags[2] == '\0'))
		no_newline = 0;
	if (tokens->flags && !tokens->args && tokens->flags[0] == '-' && \
	(tokens->flags[2] != ' ' || tokens->flags[2] != '\0'))
		printf("%s", tokens->flags);
	if (tokens->args)
		printf("%s", tokens->args);
	if (no_newline)
		printf("\n");
}
