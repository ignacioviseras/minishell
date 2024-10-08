/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:54:20 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/08 16:47:56 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* t_tree build_ast(t_token *tokens)
{
	t_tree 	ast;
	t_token	*first_token;

	first_token = tokens;
	while (tokens != NULL)
	{
		
	}
} */

void	parsing(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens != NULL)
	{
		printf("Token %i: %s\n", i++, tokens->value);
		tokens = tokens->next;
	}
}
