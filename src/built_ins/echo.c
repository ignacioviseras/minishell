/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:08 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/05 18:58:37 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_var(char *str)
{
	char	*variable;
	int		len_variable;
	int		len_all;

	len_all = 0;
	len_variable = 0;
	len_all = ft_strlen(str);
	len_variable = ft_strlen(ft_strchr(str, '='));
	variable = ft_substr(str, 0, len_all - len_variable);
	return (variable);
}

char	*get_content_var(char *str)
{
	char	*finder;
	char	*variable;
	int		start;
	int		end;

	finder = ft_strchr(str, '=');
	if (!finder || *(finder + 1) == '\0')
		return (NULL);
	finder++;
	start = 0;
	while (finder[start] == '"' || finder[start] == '\'')
		start++;
	end = ft_strlen(finder) - 1;
	while (end > start && (finder[end] == '"' || finder[end] == '\''))
		end--;
	if (start > end)
		return (ft_strdup(""));
	variable = ft_substr(finder, start, end - start + 1);
	return (variable);
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

void	command_echo(t_token *tokens)
{
	char	**str_splited;
	int		no_newline;
	int		i;

	i = 0;
	no_newline = 1;
	if (!tokens->args && !tokens->flags)
	{
		printf("\n");
		return ;
	}
	str_splited = ft_split(tokens->full_cmd, ' ');
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
