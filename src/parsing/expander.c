/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:31:45 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/07 22:15:26 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	copy_len(char *s)
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

// The same as ft_strlen but with char **
int	ft_strlen_v2(char **strs)
{
	int	i;
	int	j;
	int	total;

	j = 0;
	total = 0;
	while (strs[j])
	{
		i = 0;
		while (strs[j][i++] != '\0')
			total++;
		j++;
	}
	return (total);
}

char	*concatenate_strings(t_token *token, char **keys, char **values, int keys_nbr)
{
	char	*new_str;
	char	*str;
	int		i;
	int		j;
	int		k;

	new_str = malloc((ft_strlen(token->full_cmd) + ft_strlen_v2(values) -
					ft_strlen_v2(keys) - keys_nbr + 1) * sizeof(char));
	str = token->full_cmd;
	i = 0;
	j = 0;
	k = 0;
	/* if (ft_count_words(keys) != ft_count_words(values))
	{
		new_str = str;
		printf("%s\n", new_str);
		exit(0);
	} */
	if (!*values)
		return (str);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			new_str[k++] = str[i++];
			while (str[i] != '\'' && str[i])
				new_str[k++] = str[i++];
			if (str[i] == '\'') // Esto a lo mejor se puede quitar
				new_str[k++] = str[i++];
		}
		else if (str[i] == '"')
		{
			i++;
			if (findchar(str + i, '$') >= 0 && values[j])
			{
				ft_strcpy(new_str + k, values[j]);
				k += ft_strlen(values[j++]);
				i += findchar(str + i, '"') + 1;
			}
			else
				new_str[k++] = str[i++];
		}
		else if (str[i] == '$')
		{
			ft_strcpy(new_str + k, values[j++]);
			k += ft_strlen(values[j - 1]);
			i += copy_len(str + i) + 1;
		}
		else
			new_str[k++] = str[i++];
	}
	new_str[k] = '\0';
	printf("%s\n", new_str);
	free(str);
	exit(0);
	return (new_str);
}

void	replace_var(t_token *token, t_env *env)
{
	int		i;
	int		keys_nbr;
	char	**keys;
	char	**values;

	i = 0;
	keys_nbr = nbr_of_keys(token->full_cmd);
	keys = get_keys(token->full_cmd, keys_nbr);
	values = get_values(env, keys, keys_nbr);
	token->full_cmd = concatenate_strings(token, keys, values, keys_nbr);
	printf("%s\n", token->full_cmd);
	exit(0);
	while (values[i])
	{
	    if (keys[i] && values[i])
	        printf("Key: %s, value: %s\n", keys[i], values[i]);
	    i++;
	}
	for (i = 0; keys[i]; i++)
		free(keys[i]);
	for (i = 0; values[i]; i++)
		free(values[i]);
	free(keys);
	free(values);
}

void	expander(t_token **tokens, t_env *env)
{
	t_token	*aux;

	aux = *tokens;
	while (tokens && *tokens)
	{
		if (findchar((*tokens)->full_cmd, '$') >= 0)
			replace_var(*tokens, env);
		*tokens = (*tokens)->next;
	}
	*tokens = aux;
}
