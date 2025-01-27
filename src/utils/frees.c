/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:12:20 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/27 17:36:31 by drestrep         ###   ########.fr       */
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

//TODO: FREE REDIRECIONS ln.55
// Al parecer eso no dan leaks??

/* void	free_redirections(t_token *token)
{
	if (token->infiles)
	{
		while (token->infiles->content)
		{
			free(token->infiles->content);
			token->infiles = token->infiles->next;
		}
		free(token->infiles);
	}
	if (token->outfiles)
	{
		while (token->outfiles->content)
		{
			free(token->outfiles->content);
			token->outfiles = token->outfiles->next;
		}
		free(token->outfiles);
	}
} */

void free_redirections(t_list *redir_list)
{
    t_list          *temp;
    t_redirect_file *redir;

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
		/* if (temp->infiles)
		{
			free(temp->infiles->content);
			free(temp->infiles);
		}
		if (temp->outfiles)
		{
			free(temp->outfiles->content);
			free(temp->outfiles);
		} */
		free(temp->flags);
		free(temp->args);
		free(temp->cmd);
		free(temp->full_cmd);
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

/* void	free_env_matrix(char **env_matrix)
{
	int	i;

	i = 0;
	while (env_matrix[i])
	{
		free(env_matrix[i]);
		i++;
	}
	free(env_matrix);
} */
