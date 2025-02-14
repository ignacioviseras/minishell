/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:44:47 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 17:43:09 by igvisera         ###   ########.fr       */
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

	if (token->outfiles)
	{
		redirection = (t_redirect_file *)token->outfiles->content;
		if (redirection)
			return (redirection->type);
	}
	else if (token->infiles)
	{
		redirection = (t_redirect_file *)token->infiles->content;
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
