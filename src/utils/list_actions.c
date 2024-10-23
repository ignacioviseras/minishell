/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:14:36 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/23 11:41:13 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

t_envi	*create_node(char *content)
{
	t_envi	*envi;

	envi = malloc(sizeof(t_envi));
	if (!envi)
	{
		free(envi);
		return (NULL);
	}
	envi->content = ft_strdup(content);
	if (!envi->content)
    {
        free(envi);
        return (NULL);
    }
	envi->next = NULL;
	return (envi);
}

/*
	esto genera un error pq tiene q ser puntero doble
*/
void	add_bottom(t_envi **envi, t_envi *new_envi)
{
	t_envi	*iter;

	if (!*envi)
		*envi = new_envi;
	else
	{
		iter = *envi;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new_envi;
	}
}
