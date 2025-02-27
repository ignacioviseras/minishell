/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:31:45 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/26 17:38:13 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_word_len(char *full_cmd, int i)
{
	char	quote;

	while (full_cmd[i] && full_cmd[i] != ' ')
	{
		if (full_cmd[i] == '"' || full_cmd[i] == '\'')
		{
			quote = full_cmd[i++];
			while (full_cmd[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

char	*append_new_var(char *cmd, char *str, int caller)
{
	char	*new_var;
	char	*word;

	new_var = NULL;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		word = get_next_word(cmd, str, 1);
		if (word == NULL || word[0] == '\0')
		{
			free(word);
			break ;
		}
		if (word[0] == '-' && caller == 0)
			new_var = append_str(new_var, word);
		else if (word[0] != '-' && caller == 1)
			new_var = append_str(new_var, word);
		str += ft_strlen(word);
		free(word);
	}
	return (new_var);
}

char	*get_flags_or_args(t_token *token, char *var, int caller)
{
	char	*str;

	str = token->full_cmd + ft_strlen(token->cmd);
	while (*str && !is_alnum(*str) && *str != '-' \
		&& *str != '\'' && *str != '"')
		str++;
	free(var);
	return (append_new_var(token->cmd, str, caller));
}

void	replace_var(t_token *token, t_env *env)
{
	t_kv	kv;
	int		size;
	int		keys_nbr;

	keys_nbr = get_nbr_of_keys(token->full_cmd);
	kv.keys = get_keys(token->full_cmd, keys_nbr);
	kv.values = get_values(env, kv.keys, &keys_nbr);
	size = ft_strlen(token->full_cmd) - ft_strlen_v2(kv.keys) \
	+ ft_strlen_v2(kv.values) - keys_nbr + 1;
	token->full_cmd = expand_token(token, kv, size);
	free(token->cmd);
	token->cmd = get_command(token->full_cmd);
	if (token->flags && findchar(token->flags, '$') >= 0)
		token->flags = get_flags_or_args(token, token->flags, 0);
	if (token->args && findchar(token->args, '$') >= 0)
		token->args = get_flags_or_args(token, token->args, 1);
	free_matrix(kv.keys);
	free(kv.values);
}

void	expander(t_token **tokens, t_env *env)
{
	t_token	*start;
	char	*aux;

	start = *tokens;
	while (tokens && *tokens)
	{
		replace_var(*tokens, env);
		if ((*tokens)->type < 2 && \
			(findchar((*tokens)->cmd, '\'') >= 0 || \
			findchar((*tokens)->cmd, '\'') >= 0))
		{
			(*tokens)->cmd = remove_quotes((*tokens)->cmd);
			free((*tokens)->full_cmd);
			(*tokens)->full_cmd = ft_strjoin((*tokens)->cmd, (*tokens)->args);
		}
		*tokens = (*tokens)->next;
	}
	*tokens = start;
	aux = get_unquoted_str((*tokens)->flags);
	free((*tokens)->flags);
	(*tokens)->flags = aux;
}
