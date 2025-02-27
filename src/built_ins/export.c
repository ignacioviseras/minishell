/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:03 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/27 18:32:47 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_content_var(char *str)
{
	char	*finder;

	finder = ft_strchr(str, '=');
	if (!finder || *(finder + 1) == '\0')
		return (NULL);
	finder++;
	return (get_unquoted_str(finder));
}

char	*get_var(char *str)
{
	char	*variable;
	int		len_variable;
	int		len_all;

	len_all = 0;
	len_variable = 0;
	len_all = ft_strlen(str);
	len_variable = ft_strlen(ft_strchr(str, '='));
	variable = ft_substr(str, 0, len_all - len_variable);
	return (variable);
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

int	validate_export(char *key, char *value)
{
	if (is_valid(key) == 1)
	{
		if (value == NULL)
		{
			printf("bash: export: `%s':", key);
			printf(" not a valid identifier\n");
		}
		else
		{
			printf("bash: export: `%s=%s':", key, value);
			printf(" not a valid identifier\n");
		}
		g_exit_status = 2;
		return (1);
	}
	return (0);
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
