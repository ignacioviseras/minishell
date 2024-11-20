/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:54:59 by drestrep          #+#    #+#             */
/*   Updated: 2024/11/20 12:55:29 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	skip_input_spaces(char **input)
{
	while (*input && **input == ' ')
		(*input)++;
}

char	*skip_args_spaces(char *args)
{
	char	*aux;
	int		i;

	i = 0;
	while (args && args[i] == ' ')
		i++;
	aux = ft_strdup(args + i);
	free(args);
	return (aux);
}
