/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:59:18 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/26 18:10:11 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

char	*get_exit_status(int *keys_nbr)
{
	(*keys_nbr)--;
	return (ft_itoa(g_exit_status));
}

char	*get_env_var_value(t_env *env, char *key, int *keys_nbr)
{
	t_env	*aux;
	char	*value;

	aux = env;
	while (env && *keys_nbr > 0)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
		if (!env)
		{
			value = "";
			(*keys_nbr)--;
		}
	}
	env = aux;
	return (value);
}

char	*get_value(t_env *env, char *key, int *keys_nbr)
{
	if (ft_strcmp(key, "?") == 0)
		return (get_exit_status(keys_nbr));
	else
		return (get_env_var_value(env, key, keys_nbr));
}

char	**get_values(t_env *env, char **keys, int *keys_nbr)
{
	char	**values;
	char	*value;
	int		i;

	values = ft_malloc((*keys_nbr + 1) * sizeof(char *));
	i = 0;
	while (keys[i] && *keys_nbr > 0)
	{
		value = get_value(env, keys[i], keys_nbr);
		if (value)
			values[i++] = value;
	}
	values[i] = NULL;
	return (values);
}
