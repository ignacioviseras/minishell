/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:04:57 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/20 15:28:37 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	organize_tokens(t_token *tokens)
{
	t_token	*aux;

	aux = tokens;
	/* while (tokens)
	{
		if (tokens->next->type == TOKEN_OUTPUT || \
			tokens->next->type == TOKEN_APPEND)
		{
			tokens->flags = ft_strdup()
		}
		printf("%s\n\n", tokens->full_cmd);
		tokens = tokens->next;
	} */
	tokens = aux;
	//exit(0);
}
