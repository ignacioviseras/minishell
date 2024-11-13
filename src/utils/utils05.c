/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils05.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:26:04 by igvisera          #+#    #+#             */
/*   Updated: 2024/11/13 16:08:59 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"


int	ft_count_words(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	ft_isalnum(char	c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int is_alpha(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int is_number(char c)
{
    return (c >= '0' && c <= '9');
}

int is_alnum(char c)
{
    return (is_alpha(c) || is_number(c));
}

int is_valid(char *str)
{
    int i;

	i = 1;
	if (!str || (!is_alpha(str[0]) && str[0] != '_'))
        return (1);
    while (str[i] != '\0')
	{
        if (!is_alnum(str[i]) && str[i] != '_')
            return (1);
        i++;
    }
    return (0);
}

t_env	*new_node(char *key, char *value, int hide)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
	{
		free(env);
		return (NULL);
	}
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	env->hide = hide;
	if (!env->key || (value != NULL && !env->value))
    {
        free(env->key);
        free(env->value);
        free(env);
        return (NULL);
    }
	env->next = NULL;
	return (env);
}

void	add_bottom(t_env **env, t_env *new_envi)
{
	t_env	*iter = *env;

	while (iter)
	{
		if (ft_strcmp(iter->key, new_envi->key) == 0)
		{
			if ((iter->value == NULL && new_envi->value != NULL) || \
			(iter->value != NULL && new_envi->value != NULL))
			{
				free(iter->value);
				iter->value = ft_strdup(new_envi->value);
				iter->hide = new_envi->hide;
			}
			return (free_variable(new_envi));
		}
		if (iter->next == NULL)
			break;
		iter = iter->next;
	}
	iter->next = new_envi;
}


void	remove_node(t_env **env, char *key)
{
	t_env	*temp;
	t_env	*prev;

	if (!env || !*env)
		return;
	if (ft_strcmp((*env)->key, key) == 0)
	{
		temp = *env;
		*env = (*env)->next;
		free_variable(temp);
		return;
	}
	prev = *env;
	temp = (*env)->next;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			prev->next = temp->next;
			free_variable(temp);
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}
