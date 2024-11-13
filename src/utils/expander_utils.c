/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:41:52 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/13 15:21:56 by drestrep         ###   ########.fr       */
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

char	**get_values(t_env *env, char **keys, int keys_nbr)
{
	t_env	*aux;
	char	**values;
	int		i;

	aux = env;
	values = ft_malloc((keys_nbr + 1) * sizeof(char *));
	i = 0;
	while (keys[i] && i <= keys_nbr)
	{
		values[i] = NULL;
		while (env)
		{
			if (ft_strcmp(keys[i], env->key) == 0)
			{
				values[i] = ft_strdup(env->value);
				break ;
			}
			env = env->next;
		}
		env = aux;
		i++;
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
