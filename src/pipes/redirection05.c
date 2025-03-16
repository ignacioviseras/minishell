/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection05.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:32:59 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 17:44:01 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value_heredoc(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*expand_buffer(char *result, size_t *buf_size, size_t required_size)
{
	*buf_size = required_size * 2;
	result = ft_realloc(result, ft_strlen(result) + 1, *buf_size);
	if (!result)
	{
		perror("ft_realloc");
		exit(EXIT_FAILURE);
	}
	return (result);
}

char	*expand_variable_heredoc(const char **p, t_env *env, char *result,
		size_t *buf_size)
{
	char	varname[128];
	int		i;
	char	*value;

	(*p)++;
	i = 0;
	while (**p && (((**p >= 'a' && **p <= 'z') || (**p >= 'A' && **p <= 'Z')
				|| (**p >= '0' && **p <= '9') || (**p == '_')) && i < 127))
	{
		varname[i++] = **p;
		(*p)++;
	}
	varname[i] = '\0';
	value = get_env_value_heredoc(env, varname);
	if (value)
	{
		if (ft_strlen(result) + ft_strlen(value) + 1 > *buf_size)
			result = expand_buffer(result, buf_size, ft_strlen(result)
					+ ft_strlen(value) + 1);
		ft_strcat(result, value);
	}
	return (result);
}

char	*append_char_to_result(char *result, size_t *buf_size, const char **p)
{
	size_t	current_len;
	size_t	old_size;

	current_len = ft_strlen(result);
	if (current_len + 2 > *buf_size)
	{
		old_size = *buf_size;
		*buf_size *= 2;
		result = ft_realloc(result, old_size, *buf_size);
		if (!result)
		{
			perror("ft_realloc");
			exit(EXIT_FAILURE);
		}
	}
	result[current_len] = **p;
	result[current_len + 1] = '\0';
	(*p)++;
	return (result);
}

char	*expand_variables_heredoc(const char *line, t_env *env)
{
	char		*result;
	const char	*p;
	size_t		len;
	size_t		buf_size;

	len = ft_strlen(line);
	buf_size = len * 2 + 1;
	result = ft_malloc(buf_size);
	if (!result)
	{
		perror("ft_malloc");
		exit(EXIT_FAILURE);
	}
	result[0] = '\0';
	p = line;
	while (*p)
	{
		if (*p == '$')
			result = expand_variable_heredoc(&p, env, result, &buf_size);
		else
			result = append_char_to_result(result, &buf_size, &p);
	}
	return (result);
}
