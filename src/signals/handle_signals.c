/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:36:19 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/24 19:41:19 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    signals_handler_for_blockers(int sig)
{
	unlink(".heredoc.tmp");
    if (sig == SIGQUIT)
        printf("Quit (core dumped)");
    printf("\n");
}

void	signals_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void    son_signal(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
}

void	handle_signals(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
