/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils06.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:20:14 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/07 15:07:16 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	t_env	*iter;

	iter = *env;
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
			break ;
		iter = iter->next;
	}
	iter->next = new_envi;
}

void	remove_node(t_env **env, char *key)
{
	t_env	*temp;
	t_env	*prev;

	if (!env || !*env)
		return ;
	if (ft_strcmp((*env)->key, key) == 0)
	{
		temp = *env;
		*env = (*env)->next;
		free_variable(temp);
		return ;
	}
	prev = *env;
	temp = (*env)->next;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			prev->next = temp->next;
			free_variable(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
