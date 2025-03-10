/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:08 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/10 19:28:52 by igvisera         ###   ########.fr       */
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

void	command_echo(char *input)
{
	char	**str_splited;
	int		no_newline;
	int		i;

	i = 0;
	no_newline = 1;
	if (!input)
	{
		printf("\n");
		return ;
	}
	str_splited = ft_split(input, ' ');
	while (str_splited[++i] && is_option_n(str_splited[i]))
		no_newline = 0;
	while (str_splited[i])
	{
		printf("%s", str_splited[i]);
		if (str_splited[i + 1])
			printf(" ");
		i++;
	}
	if (no_newline)
		printf("\n");
	free_matrix(str_splited);
}
