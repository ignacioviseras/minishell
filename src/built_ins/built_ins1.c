/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 16:17:05 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_actions(t_token *tokens)
{
	int	x;

	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
		{
			x = flags_validator(tokens->flags, "L P");
			if (x == 0)
				printf("flags are not implemented\n");
			else
			{
				printf("bash: cd: -%c: invalid option\n", tokens->flags[x]);
				printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
			}
			return ;
		}
	}
	if (ft_strcmp(tokens->cmd, "cd") == 0 && n_words(tokens->args, ' ') > 1)
		printf("bash: cd: too many arguments\n");
	else if (chdir(tokens->args) != 0)
		printf("bash: cd: %s: No such file or directory\n", tokens->args);
}

void	command_cd(t_token *tokens)
{
	static char	*home;

	if (tokens == NULL)
		return ;
	if (home == NULL)
	{
		home = getenv("HOME");
		if (home == NULL)
			home = get_home(getenv("PWD"));
	}
	if (ft_strcmp(tokens->cmd, "cd") == 0 && \
		(tokens->args == NULL || ft_strcmp(tokens->args, "~") == 0))
	{
		if (chdir(home) != 0)
			perror("chdir");
	}
	else if (ft_strcmp(tokens->cmd, "cd") == 0 && tokens->args)
		cd_actions(tokens);
}

void	exit_program(t_env *env, t_ast *ast, t_token *tokens)
{
	free_env(env);
	free_ast(ast);
	free_tokens(tokens);
	exit(0);
}

void	handle_command(char *cleaned, t_token *tokens, t_env *env, t_ast *ast)
{
	if (ft_strcmp(cleaned, "pwd") == 0)
		command_pwd(tokens);
	else if (ft_strcmp(cleaned, "env") == 0)
		command_env(tokens, env);
	else if (ft_strcmp(cleaned, "cd") == 0)
		command_cd(tokens);
	else if (ft_strcmp(cleaned, "echo") == 0)
		command_echo(tokens);
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
