/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:31:45 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/04 17:21:09 by drestrep         ###   ########.fr       */
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
	while (s[i] && s[i] != '$' && s[i] != ' ' && s[i] != '"')
		i++;
	return (i);
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
				keys[j] = ft_substr(str, i + 1, copy_len(str + i + 1));
				j++;
				i += copy_len(str + i + 1);
			}
		}
		else
			i++;
	}
	keys[j] = NULL;
	return (keys);
}

void	replace_var(t_token *token, t_env *env)
{
	t_env	*aux;
	char	**keys;
	char	**values;
	int		i;

	aux = env;
	keys = get_key(token->cmd_args);
	values = ft_malloc((nbr_of_keys(token->cmd_args) + 1) * sizeof(char *));
	i = 0;
	(void)token;
	while (keys[i])
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
	i = 0;
	for (i = 0; values[i]; i++)
        printf("Key: %s, value: %s\n", keys[i], values[i]);
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
	while(tokens && *tokens)
	{
		if (ft_findchar((*tokens)->cmd_args, '$') >= 0)
			replace_var(*tokens, env);
		*tokens = (*tokens)->next;
	}
	*tokens = aux;
}
