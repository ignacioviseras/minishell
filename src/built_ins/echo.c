/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:08 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/17 18:46:45 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_option_n(char *str)
{
	int	i;
	int	result;

	i = 1;
	result = 1;
	//printf("len '%ld'\n", ft_strlen(str));
	//printf("str '%s'\n", str);
	if (str[0] == '-')
		return (result);
	if (str[0] != '-')
		result = 0;
	else
	{
		while (str[i] == 'n')
			i++;
		if (str[i] != '\0')
			result = 0;
	}
	//printf("1result '%d'\n", result);
	return (result);
}

void	command_echo(char *input)
{
	char	**str_splited;
	int		no_newline;
	int		i;

	i = 0;
	no_newline = 1;
	//printf("value '%s'\n", input);
	if (!input)
	{
		printf("\n");
		return ;
	}
	str_splited = ft_split(input, ' ');
	//printf("is_op_n '%d'\n", is_option_n(str_splited[i]));
	/* while (str_splited[++i] && is_option_n(str_splited[i]))
		no_newline = 0; */
	while (str_splited[i])
	{
		if (str_splited[++i] && no_newline == 0 && is_option_n(str_splited[i]))
			no_newline = 0;
		if (ft_strcmp())
			i++;
		printf("%s", str_splited[i]);
		if (str_splited[i + 1])
			printf(" ");
		i++;
	}
	if (no_newline)
		printf("\n");
	free_matrix(str_splited);
}
