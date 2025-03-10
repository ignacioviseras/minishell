/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/10 18:54:13 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_command(char *cleaned, t_token *tokens, t_env *env, t_ast *ast)
{
	g_exit_status = 0;
	if (ft_strcmp(cleaned, "pwd") == 0)
		command_pwd(tokens);
	else if (ft_strcmp(cleaned, "env") == 0)
		command_env(tokens, env);
	else if (ft_strcmp(cleaned, "cd") == 0)
		command_cd(tokens, env);
	else if (ft_strcmp(cleaned, "echo") == 0)
		command_echo(tokens->full_cmd);
	else if (ft_strcmp(cleaned, "export") == 0)
		command_export(tokens, env);
	else if (ft_strcmp(cleaned, "unset") == 0)
		command_unset(tokens, env);
	else if (ft_strcmp(cleaned, "clear") == 0)
		command_clear(tokens);
	else if (ft_strcmp(cleaned, "exit") == 0)
		exit_program(env, ast, tokens);
}

void	build_switch(t_env *env, t_ast *ast, t_token *tokens)
{
	char	*cleaned;

	if (!tokens)
		return ;
	cleaned = trim_sp(tokens->cmd);
	handle_command(cleaned, tokens, env, ast);
	free(cleaned);
}
