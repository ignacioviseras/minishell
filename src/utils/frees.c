/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:12:20 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/24 00:11:47 by drestrep         ###   ########.fr       */
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
		free(env->value);
		env = env->next;
		free(aux);
	}
}

void	free_tokens(t_ast *node)
{
	t_token	*data;

	if (!node)
		return ;
	data = node->data;
	free(data->args);
	free(data->cmd);
	free(data->cmd_args);
	free(data);
	free_tokens(node->left);
	free_tokens(node->right);
}

void	**free_all(char **str)
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