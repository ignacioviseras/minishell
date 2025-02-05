/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:52:06 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/05 18:55:28 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_pwd(char *pwd_key, t_env **env, char *new_pwd)
{
	add_bottom(env, new_node(pwd_key, new_pwd, 0));
}

void	handle_cd_flags(t_token *tokens)
{
	int	x;

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
}

char	*have_home(t_env *env)
{
	while (env)
	{
		if (ft_strcmp("HOME", env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	cd_actions(t_token *tokens, t_env *env)
{
	char	cwd[4096];

	if (tokens->flags && ft_charcmp(tokens->flags[0], '-') == 0)
	{
		handle_cd_flags(tokens);
		return ;
	}
	else if (ft_strcmp(tokens->cmd, "cd") == 0 && n_words(tokens->args,
			' ') > 1)
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
