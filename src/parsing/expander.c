/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:31:45 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/13 15:44:19 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	replace_var(t_token *token, t_env *env)
{
	int		i;
	int		keys_nbr;
	char	**keys;
	char	**values;

	i = 0;
	keys_nbr = nbr_of_keys(token->full_cmd);
	keys = get_keys(token->full_cmd, keys_nbr);
	values = get_values(env, keys, keys_nbr);
	token->full_cmd = expand_token(token, values, \
	ft_strlen(token->full_cmd) + ft_strlen_v2(values) - \
	ft_strlen_v2(keys) - keys_nbr + 1);
	printf("%s\n", token->full_cmd);
	while (values[i])
	{
		if (keys[i] && values[i])
			printf("Key: %s, value: %s\n", keys[i], values[i]);
		i++;
	}
	for (i = 0; keys[i]; i++)
		free(keys[i]);
	for (i = 0; values[i]; i++)
		free(values[i]);
	free(keys);
	free(values);
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
