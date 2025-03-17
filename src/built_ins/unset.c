/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:53:19 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/17 21:11:06 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_actions(t_token *tokens, t_env *env)
{
	char	**splt_vars;
	int		x;

	splt_vars = smart_split(tokens->args);
	if (!splt_vars)
		return ;
	x = -1;
	while (splt_vars[++x])
	{
		if (!ft_strchr(splt_vars[x], '='))
			remove_node(&env, splt_vars[x]);
		else
		{
			printf("megsahell: unset: `%s': not a valid identifier\n", \
			splt_vars[x]);
			g_exit_status = 1;
		}
	}
	free_matrix(splt_vars);
}

void	handle_unset_flags(t_token *tokens)
{
	int	x;

	x = flags_validator(tokens->flags, "f v n");
	if (x == 0)
	{
		printf("flags are not implemented\n");
		g_exit_status = 777;
	}
	else
	{
		printf("megashell: unset: -%c:", tokens->flags[x]);
		printf(" invalid option\n");
		printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
		g_exit_status = 2;
	}
}

void	command_unset(t_token *tokens, t_env *env)
{
	if (tokens->args == NULL)
	{
		printf("unset: not enough arguments\n");
		g_exit_status = 1;
		return ;
	}
	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
			handle_unset_flags(tokens);
	}
	else
		unset_actions(tokens, env);
}
