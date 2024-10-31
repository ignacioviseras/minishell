/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils05.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:26:04 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/29 01:09:21 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

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

/*
	esto genera un error pq tiene q ser puntero doble
*/
// void	add_bottom(t_env **env, t_env *new_envi)
// {
// 	t_env	*iter;

// 	if (!*env)
// 		*env = new_envi;
// 	else
// 	{
// 		iter = *env;
// 		while (iter->next != NULL)
// 			iter = iter->next;
// 		iter->next = new_envi;
// 	}
// }
void	add_bottom(t_env **env, t_env *new_envi)
{
	t_env	*iter = *env;

	while (iter)
	{
		if (ft_strcmp(iter->key, new_envi->key) == 0)
		{
			printf("la cadena'%s'\n", iter->value);

			// Si iter->value es NULL y new_envi->value tiene un valor, actualizamos
			if ((iter->value == NULL && new_envi->value != NULL) || \
			(iter->value != NULL && new_envi->value != NULL))
			{
				free(iter->value);  // Liberamos iter->value si existe, aunque en este caso debería ser NULL
				iter->value = ft_strdup(new_envi->value);
				iter->hide = new_envi->hide;
				printf("Valor actualizado: '%s' = '%s'\n", iter->key, iter->value);
			}
			free_variable(new_envi);  // Liberamos new_envi porque no lo agregaremos a la lista
			return;
		}
		if (iter->next == NULL)
			break;
		iter = iter->next;
	}
	// Si la clave no existe en la lista, añadimos el nuevo nodo al final
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
