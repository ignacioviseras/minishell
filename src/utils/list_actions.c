/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:14:36 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/22 11:26:41 by igvisera         ###   ########.fr       */
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
	envi->content = content;
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
