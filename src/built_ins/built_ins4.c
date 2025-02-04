/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:03 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/04 14:45:06 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_pwd(char *pwd_key, t_env **env, char *new_pwd)
{
	add_bottom(env, new_node(pwd_key, new_pwd, 0));
}

void	handle_variable_export(char *var, t_env *env, char *args)
{
	char	*var_name;
	char	*var_content;

	var_name = get_var(var);
	var_content = get_content_var(args);
	if (validate_export(var_name, var_content) == 0)
		add_bottom(&env, new_node(var_name, var_content, 0));
	free(var_name);
	free(var_content);
}

void	export_actions(t_token *tokens, t_env *env)
{
	int		x;
	char	**splt_vars;

	splt_vars = ft_split(tokens->args, ' ');
	if (!splt_vars)
	{
		free(splt_vars);
		return ;
	}
	x = -1;
	while (splt_vars[++x])
	{
		if (!ft_strchr(splt_vars[x], '='))
		{
			if (validate_export(splt_vars[x], NULL) == 0)
				add_bottom(&env, new_node(splt_vars[x], NULL, 1));
		}
		else
			handle_variable_export(splt_vars[x], env, tokens->args);
	}
	free_matrix(splt_vars);
}

void	command_export(t_token *tokens, t_env *env)
{
	if (tokens->args == NULL)
		print_env(env, 1);
	else
	{
		if (tokens->flags)
		{
			if (ft_charcmp(tokens->flags[0], '-') == 0)
			{
				if (flags_validator(tokens->flags, "f n p") == 0)
				{
					printf("flags are not implemented\n");
					return ;
				}
			}
		}
		else
			export_actions(tokens, env);
	}
}

void	unset_actions(t_token *tokens, t_env *env)
{
	char	**splt_vars;
	int		x;

	splt_vars = ft_split(tokens->args, ' ');
	if (!splt_vars)
		return ;
	x = -1;
	while (splt_vars[++x])
	{
		if (!ft_strchr(splt_vars[x], '='))
			remove_node(&env, splt_vars[x]);
		else
			printf("bash: unset: `%s': not a valid identifier\n", splt_vars[x]);
	}
	free_matrix(splt_vars);
	//free(splt_vars);
}

void	command_unset(t_token *tokens, t_env *env)
{
	int	x;

	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
		{
			x = flags_validator(tokens->flags, "f v n");
			if (x == 0)
				printf("flags are not implemented\n");
			else
			{
				printf("bash: unset: -%c:", tokens->flags[x]);
				printf(" invalid option\n");
				printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
			}
		}
	}
	else
		unset_actions(tokens, env);
}
