/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:31:45 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/04 03:45:03 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	between_quotes(char *str)
{
	char	quote;

	while (*str)
	{
		if (*str == '\'')
		{
			quote = *str;
			str++;
			while (str && *str != quote)
			{
				if (*str == '$')
					return (0);
				str++;
			}
		}
		else if (*str == '"')
		{
			quote = *str;
			str++;
			while (str && *str != quote)
			{
				if (*str == '$')
					return (1);
				str++;
			}
		}
		str++;
	}
	return (2);
}

int	copy_len(char *s)
{
	int	i;

	i = 0;
	while (s[i++])
	{
		if (s[i] == '$' || s[i] == '"')
			return (i - 1);
	}
	return (0);
}

void	replace_var(t_token **token, t_env *env, char **key)
{
	char	*value;

	value = NULL;
	(void)token;
	while (env)
	{
		if (ft_strcmp(*key, env->key) == 0)
			value = env->value;
		env = env->next;
	}
	if (value)
		printf("Key: %s, value: %s\n", *key, value);
	free(key);
	free(value);
	exit(0);
}

int	nbr_of_keys(char *str)
{
	int	keys;

	keys = 0;
	while (*str)
	{
		if (*str == '$')
			keys++;
		str++;
	}
	return (keys);
}

char	**get_key(char *str)
{
	char	**keys;
	int		i;
	int		j;

	i = 0;
	j = 0;
	keys = ft_malloc((nbr_of_keys(str) + 1) * sizeof(char *));
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (between_quotes(str) > 0)
			{
				keys[j] = ft_substr(str, i + 1, copy_len(str + i));
				j++;
			}
		}
		i++;
	}
	keys[j] = NULL;
	return (keys);
}

void	expander(t_token **tokens, t_env *env)
{
	t_token	*aux;
	char	**var;

	aux = *tokens;
	while(tokens && *tokens)
	{
		var = get_key((*tokens)->cmd_args);
		if (*var)
			replace_var(tokens, env, var);
		free(var);
		*tokens = (*tokens)->next;
	}
	*tokens = aux;
}
