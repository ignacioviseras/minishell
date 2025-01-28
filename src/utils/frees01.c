/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:12:20 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/28 17:58:25 by drestrep         ###   ########.fr       */
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

void	free_redirections(t_list *redir_list)
{
	t_list			*temp;
	t_redirect_file	*redir;

	while (redir_list)
	{
		temp = redir_list->next;
		redir = redir_list->content;
		free(redir->value);
		free(redir);
		free(redir_list);
		redir_list = temp;
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
		free_redirections(temp->infiles);
		free_redirections(temp->outfiles);
		free(temp->flags);
		free(temp->args);
		free(temp->cmd);
		free(temp->full_cmd);
		free(temp);
	}
}
