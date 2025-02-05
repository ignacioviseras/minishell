/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:54:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/05 17:37:44 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

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
