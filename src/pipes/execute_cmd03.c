/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:44:47 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 17:55:57 by igvisera         ###   ########.fr       */
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
