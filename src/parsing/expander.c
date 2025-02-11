/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:31:45 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/11 20:07:30 by drestrep         ###   ########.fr       */
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

char	*get_command(char *full_cmd)
{
	char	*cmd;
	int		i;

	i = 0;
	while (full_cmd[i] == ' ')
		i++;
	cmd = ft_substr(full_cmd, i, get_word_len(full_cmd, i));
	return (cmd);
}

char	*get_flags_or_args(t_token *token, char *var, int caller)
{
	char	*new_var;
	char	*word;
	char	*str;

	new_var = NULL;
	str = token->full_cmd + ft_strlen(token->cmd);
	while (*str && !is_alnum(*str) && *str != '-' \
		&& *str != '\'' && *str != '"')
		str++;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
 		word = get_next_word(token->cmd, str, 1);
		if (word == NULL || word[0] == '\0')
		{
			free(word);
			break ;
		}
		if (word[0] == '-' && caller == 0)
			new_var = append_str(new_var, word);
		else if (word[0] != '-' && caller == 1)
			new_var = append_str(new_var, word);
		/* if (*str == '\'' || *str == '"')
			str++; */
		str += ft_strlen(word);
		free(word);
	}
	free(var);
	return (new_var);
}

void	replace_var(t_token *token, t_env *env)
{
	int		size;
	int		keys_nbr;
	char	**keys;
	char	**values;

	keys_nbr = get_nbr_of_keys(token->full_cmd);
	keys = get_keys(token->full_cmd, keys_nbr);
	values = get_values(env, keys, &keys_nbr);
	size = ft_strlen(token->full_cmd) - ft_strlen_v2(keys) \
	+ ft_strlen_v2(values) - keys_nbr + 1;
	token->full_cmd = expand_token(token, values, size);
	free(token->cmd);
	token->cmd = get_command(token->full_cmd);
	if (token->flags && findchar(token->flags, '$') >= 0)
		token->flags = get_flags_or_args(token, token->flags, 0);
	if (token->args && findchar(token->args, '$') >= 0)
		token->args = get_flags_or_args(token, token->args, 1);
	free_matrix(keys);
	if (ft_strcmp(*values, ""))
		free_matrix(values);
	else
		free(values);
}

/* void	replace_var(t_token *token, t_env *env)
{
	int		keys_nbr;
	char	**keys;
	char	**values;

	keys_nbr = get_nbr_of_keys(token->full_cmd);
	keys = get_keys(token->full_cmd, keys_nbr);
	values = get_values(env, keys, &keys_nbr);
	token->full_cmd = expand_token(token, values, );
	token->cmd = expand_token(NULL, token->cmd, values);
	token->flags = expand_token(NULL, token->flags, values);
	token->args = expand_token(token->cmd, token->args, values);
	free_matrix(keys);
	if (ft_strcmp(*values, ""))
		free_matrix(values);
	else
		free(values);
} */

void	expander(t_token **tokens, t_env *env)
{
	t_token	*start;
	char	*aux;

	start = *tokens;
	while (tokens && *tokens)
	{
		if (findchar((*tokens)->full_cmd, '$') >= 0)
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
