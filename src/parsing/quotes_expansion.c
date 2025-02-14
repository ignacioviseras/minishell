/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:26:58 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/14 17:44:16 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_between_single_quotes(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		else if (str[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

char	*unquote(char *new_str, char *old_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_str[i])
	{
		if (old_str[i] == '"')
		{
			i++;
			while (old_str[i] && old_str[i] != '"')
				new_str[j++] = old_str[i++];
			if (old_str[i] == '"')
				i++;
		}
		else
			new_str[j++] = old_str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*remove_double_quotes(char *str)
{
	char	*unquoted_str;
	int		nbr_of_quotes;

	if (findchar(str, '"') < 0 || is_between_single_quotes(str))
		return (ft_strdup(str));
	nbr_of_quotes = count_quotes(str);
	unquoted_str = ft_malloc((ft_strlen(str) - nbr_of_quotes + 1) \
	* sizeof(char));
	return (unquote(unquoted_str, str));
}
