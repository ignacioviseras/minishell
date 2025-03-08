/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:36:19 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/08 17:46:49 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signals_handler_for_blockers(int sig)
{
	unlink(".heredoc.tmp");
	if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		printf("Quit (core dumped)");
	}
	if (sig == SIGINT)
		g_exit_status = 130;
	printf("\n");
}

//TODO: Puede (y seguramente sea) modificado.
void	heredoc_signals_handler(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		//printf("\n");
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (sig == SIGINT)
			exit (130);
		else
			exit (131);
	}
}


void	signals_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	son_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signals(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, SIG_IGN);
}

// void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	unlink(".heredoc.tmp");
// 	exit(1);
// }