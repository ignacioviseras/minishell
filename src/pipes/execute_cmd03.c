/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:44:47 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/13 16:11:08 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_path(char **env, t_params *p, t_token *t)
{
	int	x;

	x = 0;
	while (env[x])
	{
		if (ft_strncmp("PATH=", env[x], 5) == 0)
			tramited(p->env[x] + 5, p, t);
		x++;
	}
	tramited("", p, t);
}

int	have_path(char **env)
{
	int	x;

	x = 0;
	while (env[x])
	{
		if (ft_strncmp("PATH=", env[x], 5) == 0)
			return (1);
		x++;
	}
	return (0);
}

int	have_redirection(t_token *token)
{
	t_redirect_file	*redirection;

	if (token->redir)
	{
		redirection = (t_redirect_file *)token->redir->content;
		if (redirection)
			return (redirection->type);
	}
	return (-1);
}

void	create_env(t_env *env, char **envp)
{
	while (envp && *envp)
	{
		env->key = ft_substr(*envp, 0, findchar(*envp, '='));
		env->value = ft_substr(*envp, findchar(*envp, '=') + 1, findchar(*envp,
					'\0'));
		env->hide = 0;
		if (*(envp + 1))
			env->next = ft_malloc(sizeof(t_env));
		else
			env->next = NULL;
		env = env->next;
		envp++;
	}
}

void	create_env_null(t_env **env)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		*env = new_node("PWD", cwd, 0);
}
