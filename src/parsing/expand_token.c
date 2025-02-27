/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:54:03 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/26 17:42:10 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_dollar_sign(t_kv kv, const char *str, char *new_str, \
							t_counters *counters)
{
	if (!is_alnum(str[counters->i + 1]) && str[counters->i + 1] != '_' \
		&& str[counters->i + 1] != '?' && str[counters->i + 1] != '"' \
		&& str[counters->i + 1] != '\'')
	{
		new_str[counters->k++] = str[counters->i++];
		counters->j++;
	}
	else
	{
		ft_strcpy(new_str + counters->k, kv.values[counters->j++]);
		counters->k += ft_strlen(kv.values[counters->j - 1]);
		if (str[counters->i + 2] && !is_alnum(str[counters->i + 2]) \
			&& str[counters->i + 2] != '?' && str[counters->i + 2] != ' ')
			counters->i += ft_strlen(kv.keys[counters->j - 1]);
		else
			counters->i += ft_strlen(kv.keys[counters->j - 1]) + 1;
		if (ft_strcmp(kv.values[counters->j - 1], ""))
			free(kv.values[counters->j - 1]);
	}
}

void	handle_double_quote(t_kv kv, const char *old_str, char *new_str, \
							t_counters *counters)
{
	counters->i++;
	while (old_str[counters->i] && old_str[counters->i] != '"')
	{
		if (old_str[counters->i] == '$')
			handle_dollar_sign(kv, old_str, new_str, counters);
		else
			new_str[counters->k++] = old_str[counters->i++];
	}
	if (old_str[counters->i] == '"')
		counters->i++;
}

void	handle_single_quote(const char *str, char *new_str, \
							t_counters *counters)
{
	counters->i++;
	while (str[counters->i] != '\'' && str[counters->i])
		new_str[counters->k++] = str[counters->i++];
	counters->i++;
}

void	process_string(t_kv kv, char *full_cmd, char *new_str)
{
	t_counters	counters;

	counters.i = 0;
	counters.j = 0;
	counters.k = 0;
	while (full_cmd[counters.i])
	{
		if (full_cmd[counters.i] == '\'')
			handle_single_quote(full_cmd, new_str, &counters);
		else if (full_cmd[counters.i] == '"')
			handle_double_quote(kv, full_cmd, new_str, &counters);
		else if (full_cmd[counters.i] == '$')
			handle_dollar_sign(kv, full_cmd, new_str, &counters);
		else
			new_str[counters.k++] = full_cmd[counters.i++];
	}
	new_str[counters.k] = '\0';
}

char	*expand_token(t_token *token, t_kv kv, int size)
{
	char	*new_str;

	new_str = ft_malloc((size + 1) * sizeof(char));
	process_string(kv, token->full_cmd, new_str);
	free(token->full_cmd);
	return (new_str);
}
