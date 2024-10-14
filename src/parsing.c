/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:54:20 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/14 18:34:22 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast *create_ast_node(token_type type, char *data)
{
	t_ast *node;
	
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->data = data;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*parsing(t_token **tokens)
{
	t_ast	*node;
	int		i = 0;

	while (tokens && *tokens != NULL)
	{
		printf("Token %i: %s\n", i++, (*tokens)->value);
		*tokens = (*tokens)->next;
	}
	exit(0);
	if ((*tokens)->type == TOKEN_STRING)
	{
		node = create_ast_node(TOKEN_STRING, (*tokens)->value);
		*tokens = (*tokens)->next;
	}
	else if ((*tokens)->type == TOKEN_PIPE)
	{
		node = create_ast_node(TOKEN_PIPE, (*tokens)->value);
		*tokens = (*tokens)->next;
		node->left = parsing(tokens);  // Parse the command on the left of the pipe
		node->right = parsing(tokens); // Parse the command on the right of the pipe
	}
	else if ((*tokens)->type == TOKEN_OUTPUT)
	{
		node = create_ast_node(TOKEN_OUTPUT, (*tokens)->value);
		*tokens = (*tokens)->next;
		node->left = parsing(tokens);
		node->right = parsing(tokens);
	}
	else if ((*tokens)->type == TOKEN_APPEND)
	{
		node = create_ast_node(TOKEN_APPEND, (*tokens)->value);
		*tokens = (*tokens)->next;
		node->left = parsing(tokens);
		node->right = parsing(tokens);
	}
	else if ((*tokens)->type == TOKEN_INPUT)
	{
		node = create_ast_node(TOKEN_INPUT, (*tokens)->value);
		*tokens = (*tokens)->next;
		node->left = parsing(tokens);
		node->right = parsing(tokens);
	}
	else if ((*tokens)->type == TOKEN_HEREDOC)
	{
		node = create_ast_node(TOKEN_HEREDOC, (*tokens)->value);
		*tokens = (*tokens)->next;
		node->left = parsing(tokens);
		node->right = parsing(tokens);
	}
	return (node);
}
