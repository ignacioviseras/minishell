/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:52:06 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/04 17:53:38 by igvisera         ###   ########.fr       */
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
			printf("bash: unset: `%s': not a valid identifier\n", splt_vars[x]);
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
		printf("bash: unset: -%c:", tokens->flags[x]);
		printf(" invalid option\n");
		printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
		g_exit_status = 2;
	}
}

void	handle_cd_flags(t_token *tokens)
{
	int	x;

	x = flags_validator(tokens->flags, "L P");
	if (x == 0)
	{
		printf("flags are not implemented\n");
		g_exit_status = 777;
	}
	else
	{
		printf("bash: cd: -%c: invalid option\n", tokens->flags[x]);
		printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
		g_exit_status = 2;
	}
}
