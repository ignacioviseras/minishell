/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:31:45 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/07 02:42:15 by drestrep         ###   ########.fr       */
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

int	ft_isalphanum(char	c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

char	**get_keys(char *str)
{
	char	**keys;
	int		i;
	int		j;

	i = 0;
	j = 0;
	keys = ft_malloc((nbr_of_keys(str) + 1) * sizeof(char *));
	while (str[i] && j < nbr_of_keys(str))
	{
		if (str[i] == '\'')
			i += findchar(str + i + 1, '\'') + 2;
		else if (str[i] == '"')
		{
			i++;
			keys[j++] = ft_substr(str + i, findchar(str + i, '$') + 1, \
			copy_len(str + i + findchar(str + i, '$')));
			while (str[i] && str[i] != '"')
				i++;
			i++;
		}
		else if (str[i] == '$')
		{
			keys[j++] = ft_substr(str, i + 1, copy_len(str + i));
			i += copy_len(str + i) + 1;
		}
		else
			i++;
	}
	while (j < nbr_of_keys(str) + 1)
		keys[j++] = NULL;
	return (keys);
}

void	replace_var(t_token **token, t_env *env)
{
	t_env	*aux;
	char	**keys;
	char	**values;
	int		i;

	aux = env;
	keys = get_keys((*token)->full_cmd);
	values = ft_malloc((nbr_of_keys((*token)->full_cmd) + 1) * sizeof(char *));
	i = 0;
	while (keys[i])
		printf("%s\n", keys[i++]);
	(void)token;
	i = 0;
	while (keys[i] && i < nbr_of_keys((*token)->full_cmd))
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
	while (values[i])
	{
	    if (keys[i] && values[i])  // Ensure neither is null
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
	while(tokens && *tokens)
	{
		if (findchar((*tokens)->full_cmd, '$') >= 0)
			replace_var(tokens, env);
		*tokens = (*tokens)->next;
	}
	*tokens = aux;
}
