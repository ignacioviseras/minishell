/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:37 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/05 18:51:11 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	flags_validator(char *flags, char *command_flags)
{
	int		i;
	int		j;
	int		valid_flag;
	char	**cmd_flags_splited;

	if (ft_strcmp(flags, "--help") == 0)
		return (0);
	i = 0;
	cmd_flags_splited = ft_split(command_flags, ' ');
	while (flags[++i] != '\0')
	{
		j = -1;
		valid_flag = 0;
		while (cmd_flags_splited[++j])
		{
			if (ft_charcmp(flags[i], cmd_flags_splited[j][0]) == 0)
			{
				valid_flag = 1;
				break ;
			}
		}
		if (!valid_flag)
			return (free_matrix(cmd_flags_splited), i);
	}
	return (free_matrix(cmd_flags_splited), 0);
}

void	command_pwd(t_token *tokens)
{
	int		x;
	char	cwd[4096];

	if (tokens->flags && ft_charcmp(tokens->flags[0], '-') == 0)
	{
		x = flags_validator(tokens->flags, "L P");
		if (x == 0)
			printf("flags are not implemented\n");
		else
		{
			printf("bash: pwd: -%c: invalid option\n", tokens->flags[x]);
			printf("pwd: usage: pwd [-LP]\n");
		}
		g_exit_status = 2;
	}
	else if (tokens->args == NULL || ft_strcmp(tokens->args, "") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
	}
}
