/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:04:57 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/04 13:02:26 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	organize_tokens(t_token *tokens)
{
	t_token	*aux;

	aux = tokens;
	while (tokens)
	{
		if (tokens->next && tokens->next->type > 1)
		{
			if (tokens->next->next->flags)
			{
				tokens->flags = ft_strdup(tokens->next->next->flags);
				tokens->next->next->flags = NULL;
			}
			if (tokens->next->next->args)
			{
				tokens->args = ft_strdup(tokens->next->next->args);
				tokens->next->next->args = NULL;
				free(tokens->next->next->full_cmd);
				tokens->next->next->full_cmd = \
				ft_strdup(tokens->next->next->cmd);
			}
			free(tokens->full_cmd);
			tokens->full_cmd = ft_strjoin(tokens->cmd, tokens->args);
		}
		/* else if (tokens->next && tokens->type > 1)
		{
			if (tokens.)
		} */
		tokens = tokens->next;
	}
	tokens = aux;
}
