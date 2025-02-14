/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection05.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:32:59 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 16:03:35 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_env_value_heredoc(t_env *env, const char *key)
{
    while (env)
	{
        if (ft_strcmp(env->key, key) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}


char *expand_buffer(char *result, size_t *buf_size, size_t required_size)
{
    *buf_size = required_size * 2;
    result = ft_realloc(result, *buf_size);
    if (!result)
    {
        perror("ft_realloc");
        exit(EXIT_FAILURE);
    }
    return result;
}

char *expand_variable_heredoc(const char **p, t_env *env, char *result, size_t *buf_size)
{
    char varname[128];
    int i;
    char *value;

    (*p)++; /* Salta el '$' */
    i = 0;
    while (**p && (((**p >= 'a' && **p <= 'z') ||
                    (**p >= 'A' && **p <= 'Z') ||
                    (**p >= '0' && **p <= '9') ||
                    (**p == '_')) && i < 127))
    {
        varname[i++] = **p;
        (*p)++;
    }
    varname[i] = '\0';
    value = get_env_value_heredoc(env, varname);
    if (value)
    {
        if (ft_strlen(result) + ft_strlen(value) + 1 > *buf_size)
            result = expand_buffer(result, buf_size, ft_strlen(result) + ft_strlen(value) + 1);
        ft_strcat(result, value);
    }
    return result;
}
