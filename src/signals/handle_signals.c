/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:36:19 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/07 15:13:33 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_signal_caught;

void signals_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
		g_signal_caught = 1;
	}
	if (sig == SIGQUIT)
	{
		printf("^\\Quit (core dumped)");
		g_signal_caught = 2;
	}
}

void	handle_signals(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, signals_handler);
}
