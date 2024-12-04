/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:31:45 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/04 16:07:33 by drestrep         ###   ########.fr       */
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

int	compute_expand_size(char *cmd, char **keys, char **values, int keys_nbr)
{
	int	original_len;
	int	values_len;
	int	keys_len;

	original_len = ft_strlen(cmd);
	values_len = ft_strlen_v2(values);
	keys_len = ft_strlen_v2(keys);
	return (original_len - keys_len + values_len - keys_nbr + 1);
}

void	replace_var(t_token *token, t_env *env)
{
	int		size;
	int		keys_nbr;
	char	**keys;
	char	**values;

	keys_nbr = nbr_of_keys(token->full_cmd);
	keys = get_keys(token->full_cmd, keys_nbr);
	values = get_values(env, keys, &keys_nbr);
	size = compute_expand_size(token->full_cmd, keys, values, keys_nbr);
	token->full_cmd = expand_token(token, values, size);
	free(token->cmd);
	token->cmd = get_command(token->full_cmd);
	if (token->args)
	{
		free(token->args);
		token->args = ft_strdup(token->full_cmd + ft_strlen(token->cmd));
		token->args = skip_args_spaces(token->args);
	}
	free_expander_vars(keys, values);
}

void	expander(t_token **tokens, t_env *env)
{
	t_token	*aux;

	aux = *tokens;
	while (tokens && *tokens)
	{
		if (findchar((*tokens)->full_cmd, '$') >= 0)
			replace_var(*tokens, env);
		if ((*tokens)->type < 2)
		{
			(*tokens)->cmd = remove_quotes((*tokens)->cmd);
			free((*tokens)->full_cmd);
			(*tokens)->full_cmd = ft_strjoin((*tokens)->cmd, (*tokens)->args);
		}
		*tokens = (*tokens)->next;
	}
	*tokens = aux;
}
