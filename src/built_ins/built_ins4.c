/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:03 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/04 19:14:31 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_pwd(char *pwd_key, t_env **env, char *new_pwd)
{
	add_bottom(env, new_node(pwd_key, new_pwd, 0));
}

void	handle_variable_export(char *var, t_env *env)
{
	char	*var_name;
	char	*var_content;

	var_name = get_var(var);
	var_content = get_content_var(var);
	if (validate_export(var_name, var_content) == 0)
		add_bottom(&env, new_node(var_name, var_content, 0));
	free(var_name);
	free(var_content);
}

void	command_export(t_token *tokens, t_env *env)
{
	int		x;
	char	**splt_vars;

	if (tokens->args == NULL)
		print_env(env, 1);
	else
	{
		splt_vars = smart_split(tokens->args);
		if (!splt_vars)
			return ;
		x = -1;
		while (splt_vars[++x])
		{
			if (!ft_strchr(splt_vars[x], '='))
			{
				if (validate_export(splt_vars[x], NULL) == 0)
					add_bottom(&env, new_node(splt_vars[x], NULL, 1));
			}
			else
				handle_variable_export(splt_vars[x], env);
		}
		free_matrix(splt_vars);
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
