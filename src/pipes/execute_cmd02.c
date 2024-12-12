/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:36:15 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/12 09:38:03 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void	get_path(char **env, t_params *p, t_token *t)
{
	int	x;

	x = 0;
	while (env[x])
	{
		if (ft_strncmp("PATH=", env[x], 5) == 0)
			tramited(p->env[x] + 5, p, t);
		x++;
	}
	tramited("", p, t);

}

void execute_cmd(t_params *p)
{
    int i;

    i = execve(p->cmd_path, p->cmd_exec, p->env);
    if (i < 0)
    {
        perror("execve");
        g_exit_status = 126;
        exit(126);
    }
}
