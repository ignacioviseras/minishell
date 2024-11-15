/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:41:52 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/15 15:35:43 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	copy_len(const char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != '$' && s[i] != ' ' && s[i] != '\'' && s[i] != '"')
		i++;
	return (i - 1);
}

int	nbr_of_keys(char *str)
{
	int	keys = 0;

	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			str++;
		}
		else if (*str == '"')
		{
			str++;
			while (*str && *str != '"')
			{
				if (*str == '$')
					keys++;
				str++;
			}
			str++;
		}
		else if (*str == '$')
		{
			str++;
			keys++;
		}
		else
			str++;
	}
	return keys;
}

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

char	*get_key(char *str, int *i)
{
	char	*key = NULL;

	if (str[*i] == '\'')
		*i += findchar(str + *i + 1, '\'') + 2;
	else if (str[*i] == '"')
	{
		(*i)++;
		if (findchar(str + *i, '$') >= 0)
			key = ft_substr(str + *i, findchar(str + *i, '$') + 1, \
			copy_len(str + *i + findchar(str + *i, '$')));
		*i += findchar(str + *i, '"') + 1;
	}
	else if (str[*i] == '$')
	{
		key = ft_substr(str, *i + 1, copy_len(str + *i));
		*i += copy_len(str + *i) + 1;
	}
	else
		(*i)++;
	return (key);
}


char	**get_keys(char *str, int keys_nbr)
{
	char	**keys;
	char	*key;
	int		i;
	int		j;

	i = 0;
	j = 0;
	keys = ft_malloc((keys_nbr + 1) * sizeof(char *));
	while (str[i])
	{
		key = get_key(str, &i);
		if (key)
			keys[j++] = key;
	}
	keys[keys_nbr] = NULL;
	return (keys);
}
