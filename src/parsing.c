/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:54:20 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/08 17:41:53 by drestrep         ###   ########.fr       */
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

t_ast *add_ast_node(t_ast *node)
{
	if (!node->left)
	{
		node->left = node;
		node->left->data = node->data;
	}
}
t_ast *create_ast_node(token_type type, char *data)
{
	t_ast *node;
	
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->data = ft_strdup(data);
	node->left = NULL;
	node->right = NULL;
	node->type = type;
	return (node);
}

t_ast	parsing(t_token *tokens)
{
	t_ast	ast;
	t_ast	*current_node;
	int		i;

	i = 1;
	while (tokens != NULL)
	{
		printf("Token %i: %s\n", i++, tokens->value);
		tokens = tokens->next;
	}
	while (tokens->next)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			current_node = create_ast_node(TOKEN_PIPE, tokens->value);
			if (ast.data = NULL)
				ast.data = tokens->value;
			else
				add_ast_node(current_node);
		}
		else
		{
			if (ast.data = NULL)
				ast.data = tokens->value;
			else
				ast.left = tokens->value;
		}
	}
}
