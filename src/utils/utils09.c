/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils09.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:28:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/20 18:08:14 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_alpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_alnum(char c)
{
	return (is_alpha(c) || is_number(c));
}

int	valid_char_filename(char c)
{
	if (c == ' ' || c == '\\' || c == '/' || c == ':' || c == '*' || \
		c == '?' || c == '<' || c == '>' || c == '|' || c == '&')
		return (0);
	return (1);
}
