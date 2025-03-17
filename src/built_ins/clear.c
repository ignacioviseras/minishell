/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:56:10 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/17 21:33:41 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	command_clear(t_token *tokens)
{
	int	x;

	x = 2;
	if (tokens->flags && ft_charcmp(tokens->flags[0], '-') == 0)
	{
		x = flags_validator(tokens->flags, "T V x");
		if (x == 0)
		{
			printf("flags are not implemented\n");
			g_exit_status = 777;
		}
		else
			printf("clear: invalid option -- '%c'\n", tokens->flags[x]);
	}
	else if (tokens->args == NULL || ft_strcmp(tokens->args, "")==0)
		printf("\033[2J\033[H");
	if ((tokens->args != NULL && ft_strcmp(tokens->args, "")!=0) || x == 1)
	{
		printf("Usage: clear [options]\n\nOptions:\n");
		printf("  -T TERM     use this instead of $TERM\n");
		printf("  -V          print curses-version\n");
		printf("  -x          do not try to clear scrollback\n");
		g_exit_status = 1;
	}
}
