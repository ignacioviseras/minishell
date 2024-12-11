/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:54:59 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/10 14:46:34 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	skip_input_spaces(char **input)
{
	while (*input && (**input == SPACE || **input == '\t'))
		(*input)++;
}

char	*skip_args_spaces(char *args)
{
	char	*aux;
	int		i;

	i = 0;
	while (args && (args[i] == SPACE || args[i] == '\t'))
		i++;
	aux = ft_strdup(args + i);
	free(args);
	return (aux);
}
