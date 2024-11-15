/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:31:45 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/15 16:56:40 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	compute_expand_size(char *cmd, char **keys, char **values, int keys_nbr)
{
	int original_len;
	int values_len;
	int keys_len;
	
	original_len = ft_strlen(cmd);
	values_len = ft_strlen_v2(values);
	keys_len = ft_strlen_v2(keys);
	return (original_len - keys_len + values_len + keys_nbr + 1);
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
	token->cmd = ft_substr(token->full_cmd, 0, findchar(token->full_cmd, ' '));
	if (token->args)
	{
		free(token->args);
		token->args = ft_strdup(token->full_cmd + findchar(token->full_cmd, ' '));
		token->args = skip_args_spaces(token->args);
	}
	/* printf("%s\n", token->full_cmd);
	printf("%s\n", token->cmd);
	printf("%s\n", token->args); */
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
		*tokens = (*tokens)->next;
	}
	*tokens = aux;
}
