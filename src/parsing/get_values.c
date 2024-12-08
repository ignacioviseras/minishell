/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:59:18 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/07 15:04:21 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_value(t_env *env, char *key, int *keys_nbr)
{
	t_env	*aux;
	char	*value;

	aux = env;
	value = NULL;
	while (env)
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
			keys_nbr--;
		}
	}
	env = aux;
	return (value);
}

char	**get_values(t_env *env, char **keys, int *keys_nbr)
{
	char	**values;
	char	*value;
	int		i;

	values = ft_malloc((*keys_nbr + 1) * sizeof(char *));
	i = 0;
	while (keys[i] && i <= *keys_nbr)
	{
		value = get_value(env, keys[i], keys_nbr);
		if (value)
			values[i++] = value;
	}
	values[i] = NULL;
	return (values);
}
