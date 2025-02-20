/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:08 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/20 18:21:40 by drestrep         ###   ########.fr       */
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
	char	*remains;
	char	*aux;
	int		no_newline;

	no_newline = 1;
	if (ft_strcmp(tokens->flags, "-n") == 0 && !tokens->args)
		return ;
	remains = tokens->full_cmd + ft_strlen(tokens->cmd);
	while (remains && *remains == ' ')
		remains++;
	aux = get_next_word(NULL, remains, 0);
	if (ft_strcmp(aux, "-n") == 0)
	{
		no_newline = 0;
		remains += ft_strlen(aux);
	}
	while (remains && *remains == ' ')
		remains++;
	if (remains)
		printf("%s", remains);
	if (no_newline)
		printf("\n");
	free(aux);
}
