/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:54:20 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/25 17:41:02 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*create_node(void *data)
{
	t_ast	*node;

	node = ft_malloc(sizeof(t_ast));
	ft_bzero(node, sizeof(t_ast));
	node->data = data;
	return (node);
}

void	build_tree(t_token *tokens, t_ast **node)
{
	while (tokens)
	{
		if (!(*node))
			*node = create_node(tokens);
		else if (!(*node)->left)
		{
			(*node)->left = create_node((*node)->data);
			(*node)->data = tokens;
		}
		else
		{
			(*node)->right = create_node(tokens);
			build_tree(tokens->next, &(*node)->right);
			return ;
		}
		tokens = tokens->next;
	}
}

t_ast	*parsing(t_token *tokens, t_env *env)
{
	t_ast	*tree;

	if (!tokens)
		return (NULL);
	tree = NULL;
	build_tree(tokens, &tree);
	expander(&tokens, env);
	(void)env;
	return (tree);
}
