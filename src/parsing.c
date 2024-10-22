/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:54:20 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/22 06:31:12 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast	*create_node(void *data)
{
	t_ast	*node;

	node = ft_malloc(sizeof(t_ast));
	ft_bzero(node, sizeof(t_ast));
	node->data = data;
	return (node);
}

void	build_tree(t_token **tokens, t_ast **current_node)
{
	while (*tokens)
	{
		if (!(*current_node)->data)
			(*current_node)->data = *tokens;
		else if (!(*current_node)->left)
		{
			(*current_node)->left = create_node((*current_node)->data);
			(*current_node)->data = *tokens;
		}
		else
		{
			(*current_node)->right = create_node(*tokens);
			build_tree(&(*tokens)->next, &(*current_node)->right);
			return ;
		}
		*tokens = (*tokens)->next;
	}
}

t_ast	*parsing(t_token *tokens, t_env *env)
{
	t_ast	*tree;
	t_ast	*node;

	if (!tokens)
		return (NULL);
	node = create_node(NULL);
	tree = node;
	build_tree(&tokens, &node);
	(void)env;
	return (tree);
}
