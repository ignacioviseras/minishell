/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:54:03 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/11 19:51:27 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_dollar_sign(const char *str, char *new_str, char **values, \
							t_counters *counters)
{
	if (!is_alpha(str[counters->i + 1]) && str[counters->i + 1] != '_' \
		&& str[counters->i + 1] != '?')
		new_str[counters->k++] = str[counters->i++];
	else
	{
		ft_strcpy(new_str + counters->k, values[counters->j++]);
		counters->k += ft_strlen(values[counters->j - 1]);
		counters->i += copy_len(str + counters->i) + 1;
	}
}

void	handle_double_quote(const char *str, char *new_str, char **values, \
							t_counters *counters)
{
	new_str[counters->k++] = str[counters->i++];
	while (str[counters->i] && str[counters->i] != '"')
	{
		if (str[counters->i] == '$')
			handle_dollar_sign(str, new_str, values, counters);
		else
			new_str[counters->k++] = str[counters->i++];
	}
	if (str[counters->i] == '"')
		new_str[counters->k++] = str[counters->i++];
}

void	handle_single_quote(const char *str, char *new_str, \
							t_counters *counters)
{
	new_str[counters->k++] = str[counters->i++];
	while (str[counters->i] != '\'' && str[counters->i])
		new_str[counters->k++] = str[counters->i++];
	new_str[counters->k++] = str[counters->i++];
}

void	process_string(char *full_cmd, char *new_str, char **values, \
						t_counters *counters)
{
	while (full_cmd[counters->i])
	{
		if (full_cmd[counters->i] == '\'')
			handle_single_quote(full_cmd, new_str, counters);
		else if (full_cmd[counters->i] == '"')
			handle_double_quote(full_cmd, new_str, values, counters);
		else if (full_cmd[counters->i] == '$')
			handle_dollar_sign(full_cmd, new_str, values, counters);
		else
			new_str[counters->k++] = full_cmd[counters->i++];
	}
	new_str[counters->k] = '\0';
}

char	*expand_token(t_token *token, char **values, int size)
{
	char		*new_str;
	t_counters	counters;

	counters.i = 0;
	counters.j = 0;
	counters.k = 0;
	new_str = ft_malloc((size + 1) * sizeof(char));
	process_string(token->full_cmd, new_str, values, &counters);
	free(token->full_cmd);
	return (new_str);
}
