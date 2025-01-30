/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:34:57 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/30 15:01:04 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	command_clear(t_token *tokens)
{
	int	x;

	x = 2;
	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
		{
			x = flags_validator(tokens->flags, "T V x");
			if (x == 0)
				printf("flags are not implemented\n");
			else
				printf("clear: invalid option -- '%c'\n", tokens->flags[x]);
		}
	}
	else if (tokens->args == NULL)
		printf("\033[2J\033[H");
	if (tokens->args != NULL || x == 1)
	{
		printf("Usage: clear [options]\n\nOptions:\n");
		printf("  -T TERM     use this instead of $TERM\n");
		printf("  -V          print curses-version\n");
		printf("  -x          do not try to clear scrollback\n");
	}
}

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

void	print_echo(char *input)
{
	char	**str_splited;
	int		no_newline;
	int		i;

	i = -1;
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

void	command_echo(t_token *tokens)
{
	int	x;

	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
		{
			x = flags_validator(tokens->flags, "e E");
			if (x == 0)
				printf("flags are not implemented\n");
			else
				print_echo(tokens->args);
		}
	}
	else
		print_echo(tokens->args);
}
