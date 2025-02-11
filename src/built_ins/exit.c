/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:51:58 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/11 15:23:55 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_imposter(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

/* void	get_new_exit_status(char *full_cmd, char *flags, int i)
{
	char	*nbr;

	nbr = get_next_word(full_cmd + i);
	if ((full_cmd[i] == '-' && find_imposter(full_cmd + i + 1)) || \
		(full_cmd[i] == '-' && full_cmd[i + 1] != '-' \
		&& !is_number(full_cmd[i + 1])))
	{
		g_exit_status = 2;
		printf("megashell: exit: %s: numeric argument required\n", flags);
	}
	else if (findchar(full_cmd + i, ' ') > 0)
	{
		i += findchar(full_cmd + i, ' ');
		while (full_cmd[i] == ' ')
			i++;
		if (full_cmd[i] != '\0')
		{
			g_exit_status = 1;
			printf("megashell: exit: too many arguments\n");
		}
	}
	else if (nbr)
		g_exit_status = ft_atoi(nbr);
	free(nbr);
} */

void	exit_program(t_env *env, t_ast *ast, t_token *tokens)
{
	char	*full_cmd;
	int		i;

	i = 0;
	full_cmd = get_unquoted_str(tokens->full_cmd);
	printf("exit\n");
	while (is_alpha(full_cmd[i]))
		i++;
	skip_spaces(full_cmd, &i);
	if (full_cmd[i] == '-' && full_cmd[i + 1] == '-' && \
	(full_cmd[i + 2] == '\0' || full_cmd[i + 2] == ' '))
		i += 2;
	skip_spaces(full_cmd, &i);
	//TODO
	//get_new_exit_status(full_cmd, tokens->flags, i);
	free(full_cmd);
	free_env(env);
	free_ast(ast);
	free_tokens(tokens);
	exit(g_exit_status);
}
