/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/04 15:48:58 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_actions(t_token *tokens, t_env *env)
{
	char	cwd[4096];
	int	x;

	if (tokens->flags && ft_charcmp(tokens->flags[0], '-') == 0)
	{
		x = flags_validator(tokens->flags, "L P");
		if (x == 0)
		{
			printf("flags are not implemented\n");
			g_exit_status = 777;
		}
		else
		{
			printf("bash: cd: -%c: invalid option\n", tokens->flags[x]);
			printf("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n");
			g_exit_status = 2;
		}
		return ;
	}
	else if (ft_strcmp(tokens->cmd, "cd") == 0 && n_words(tokens->args, ' ') > 1)
		printf("bash: cd: too many arguments\n");
	else if (chdir(tokens->args) != 0)
		printf("bash: cd: %s: No such file or directory\n", tokens->args);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			update_pwd("PWD", &env, cwd);
	}
	g_exit_status = 1;
}


char	*have_home(t_env *env)
{
	while (env)
	{
		if (ft_strcmp("HOME", env->key) == 0)
			return (env->value);
		env = env ->next;
	}
	return (NULL);
}

void	command_cd(t_token *tokens, t_env *env)
{
	char	*home;
	char	cwd[4096];

	if (tokens == NULL)
		return ;
	if (tokens->args || tokens->flags)
		cd_actions(tokens, env);
	else if ((tokens->args == NULL || ft_strcmp(tokens->args, "~") == 0))
	{
		home = have_home(env);
		if (home != NULL)
		{
			if (chdir(home) != 0)
				perror("chdir");
			else if (getcwd(cwd, sizeof(cwd)) != NULL)
				update_pwd("PWD", &env, cwd);
		}
		else
		{
			printf("\t--- Error ---\ncd: HOME not set\n");
			g_exit_status = 1;
		}
	}
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
	g_exit_status = 0;
	if (ft_strcmp(cleaned, "pwd") == 0)
		command_pwd(tokens);
	else if (ft_strcmp(cleaned, "env") == 0)
		command_env(tokens, env);
	else if (ft_strcmp(cleaned, "cd") == 0)
		command_cd(tokens, env);
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
