/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:08 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/08 16:28:36 by drestrep         ###   ########.fr       */
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

/* void	print_word(char **str_splitted)
{
	printf("%s", *str_splitted);
	if (*str_splitted + 1)
		printf(" ");
	(*str_splitted)++;
}

void	command_echo(t_token *tokens)
{
	char	**str_splitted;
	//char	*unquoted;
	char	*start;
	int		no_newline;

	no_newline = 1;
	if (!tokens->args && !tokens->flags)
	{
		printf("\n");
		return ;
	}
	//unquoted = get_unquoted_str(tokens->full_cmd);
	//str_splitted = ft_split(unquoted, ' ');
	//free(unquoted);
	str_splitted = ft_split(tokens->args, ' ');
	start = *str_splitted;
	while ((*str_splitted)++ && is_option_n(*str_splitted))
		no_newline = 0;
	while (*str_splitted)
		print_word(str_splitted);
	if (no_newline)
		printf("\n");
	*str_splitted = start;
	free_matrix(str_splitted);
} */

void	command_echo(t_token *tokens)
{
	//char	*unquoted_args;
	int		no_newline;

	no_newline = 1;
	if (tokens->flags && tokens->flags[0] == '-' && tokens->flags[1] == 'n' && \
		(tokens->flags[2] == ' ' || tokens->flags[2] == '\0'))
		no_newline = 0;
	if (tokens->flags  && !tokens->args && tokens->flags[0] == '-' && \
	(tokens->flags[2] != ' ' || tokens->flags[2] != '\0'))
		printf("%s", tokens->flags); //TODO: A lo mejor se imprime con comillas si echo "-n$z"
	/* unquoted_args = get_unquoted_str(tokens->args);
	if (tokens->args)
		printf("%s", unquoted_args);
	free(unquoted_args); */
	if (tokens->args)
		printf("%s", tokens->args);
	if (no_newline)
		printf("\n");
}
