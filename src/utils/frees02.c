/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:58:42 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/14 16:15:42 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_expander_vars(char **keys, char **values)
{
	int	i;

	i = 0;
	while (keys[i])
		free(keys[i++]);
	i = 0;
	while (values[i])
	{
		if (ft_strcmp(values[i], "") < 0)
			free(values[i]);
		i++;
	}
	free(keys);
	free(values);
}
