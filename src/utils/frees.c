/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:12:20 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/28 16:55:42 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	free(node);
}

void	free_env(t_env *env)
{
	t_env	*aux;

	if (!env)
		return ;
	while (env)
	{
		aux = env;
		free(env->key);
		if (env->value)
			free(env->value);
		env = env->next;
		free(aux);
	}
}

void	free_tokens(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->flags);
		free(temp->args);
		free(temp->cmd);
		free(temp->cmd_args);
		free(temp);
	}
}

void	**free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	return (free(str), NULL);
}

void	free_variable(t_env *node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}
