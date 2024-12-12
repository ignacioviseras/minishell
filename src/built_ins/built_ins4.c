/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:03 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/12 13:48:53 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"


int validate_export(char *key, char *value)
{

	if (is_valid(key) == 1)
	{
		if (value == NULL)
		{
			printf("bash: export: `%s': not a valid identifier\n", key);
			return (1);
		}
		else
		{
			printf("bash: export: `%s=%s': not a valid identifier\n",\
				key, value);
			return (1);
		}
	}
	return (0);
}

// char *get_value(t_env **envi, char *find)
// {
//     t_env *current = *envi;
    
//     while (current)
//     {
//         if (ft_strcmp(find, current->key) == 0)
//             return (current->value);
//         current = current->next;
//     }
//     return (NULL);
// }

void export_actions(t_token *tokens, t_env *env)
{
	char	**splt_vars;
	char	*var_name;
	char	*var_content;
	int		x;

	splt_vars = ft_split(tokens->args, ' ');
	if (!splt_vars)
		return;//TODO mirar esto dara errores el control del malloc
	x = -1;
	while (splt_vars[++x])
	{
		if (!ft_strchr(splt_vars[x], '='))
		{
			if (validate_export(splt_vars[x], NULL) == 0)
				add_bottom(&env, new_node(splt_vars[x], NULL, 1));
		}
		else
		{
			var_name = get_var(splt_vars[x]);
            var_content = get_content_var(tokens->args);
            if (validate_export(var_name, var_content) == 0)
                add_bottom(&env, new_node(var_name, var_content, 0));
			free(var_name);
            free(var_content);
		}
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
					return;
				}
			}
		}
		else
			export_actions(tokens, env);
	}
}

void	unset_actions(t_token *tokens, t_env *env)
{
	char **splt_vars;
	int x;

	splt_vars = ft_split(tokens->args, ' ');
	if (!splt_vars)
		return;//TODO mirar esto dara errores el control del malloc
	x = -1;
	while (splt_vars[++x])
	{
		if (!ft_strchr(splt_vars[x], '='))
			remove_node(&env, splt_vars[x]);
		else
			printf("bash: unset: `%s': not a valid identifier\n", splt_vars[x]);
	}
	free(splt_vars);
}

void	command_unset(t_token *tokens, t_env *env)
{
	int x;
	
	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
		{
			x = flags_validator(tokens->flags, "f v n");
			if (x == 0)
				printf("flags are not implemented\n");
			else
			{
				printf("bash: unset: -%c: invalid option\n", \
				tokens->flags[x]);
				printf("unset: usage: unset [-f] [-v] [-n] [name ...]\n");
			}
		}
	}
	else
		unset_actions(tokens, env);
}
