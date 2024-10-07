/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:54:20 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/04 15:09:54 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	//t_tree	ast;
	int	i;

	i = 1;
	while (tokens != NULL)
	{
		printf("Token %i: %s\n", i++, tokens->value);
		tokens = tokens->next;
	}
	//ast = build_ast(tokens);
}
