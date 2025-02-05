/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:36:19 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/05 13:55:21 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signals_handler_for_blockers(int sig)
{
	if (sig == SIGQUIT)
		printf("Quit (core dumped)");
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	signals_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signals(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
