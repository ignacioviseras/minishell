/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/12 16:43:10 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void cd_actions(t_token *tokens)
{
	int x;

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
			return;
		}
	}
	if (ft_strcmp(tokens->cmd, "cd") == 0 && n_words(tokens->args, ' ') > 1)
		printf("bash: cd: too many arguments\n");
	else if (chdir(tokens->args) != 0)
		printf("bash: cd: %s: No such file or directory\n", tokens->args);
}

void command_cd(t_token *tokens)
{
	static char *home;

	if (tokens == NULL)
		return;
	if (home == NULL)
	{
		home = getenv("HOME");
		if (home == NULL)
			home = get_home(getenv("PWD"));
	}
	if (ft_strcmp(tokens->cmd, "cd") == 0 && 
		(tokens->args == NULL || ft_strcmp(tokens->args, "~") == 0) )
	{
		if (chdir(home) != 0)
			perror("chdir");
	}
	else if (ft_strcmp(tokens->cmd, "cd") == 0 && tokens->args)
		cd_actions(tokens);
}

void command_env(t_token *tokens, t_env *envi)
{
	int	x;

	x = 0;
	if (tokens->flags == NULL)
	{
		print_env(envi, 0);
		return;
	}
	if (ft_charcmp(tokens->flags[0], '-') == 0)
	{
		x = flags_validator(tokens->flags, "i 0 u C S v");
		if (x == 0)
			printf("flags are not implemented\n");
		else
		{
			printf("env: invalid option -- '%c'\n", tokens->flags[x]);
			printf("Try 'env --help' for more information.\n");
		}
	}
}

void build_switch(t_env *env, t_ast *ast, t_token *tokens)
{
	char *cleaned;
    printf("acedes??? '%s'\n", tokens->cmd);
    cleaned = trim_sp(tokens->cmd);
    dprintf(2, "como es el trim22 '%s'\n", cleaned);
	if (!tokens)
		return ;
	if (ft_strcmp(cleaned, "pwd") == 0)
	{
		free(cleaned);
    	dprintf(2, "accediste no?\n");
		command_pwd(tokens);
	}
	else if (ft_strcmp(cleaned, "env") == 0)
	{
		free(cleaned);
		command_env(tokens, env);
	}
	else if (ft_strcmp(cleaned, "cd") == 0)
	{
		free(cleaned);
		command_cd(tokens);
	}
	else if (ft_strcmp(cleaned, "echo") == 0)
	{
		free(cleaned);
		command_echo(tokens);
	}
	else if (ft_strcmp(cleaned, "export") == 0)
	{
		free(cleaned);
		command_export(tokens, env);
	}
	else if (ft_strcmp(cleaned, "unset") == 0)
	{
		free(cleaned);
		command_unset(tokens, env);
	}
	else if (ft_strcmp(cleaned, "clear") == 0)
	{
		free(cleaned);
		command_clear(tokens);
	}
	else if (ft_strcmp(cleaned, "exit") == 0)
	{
		free_env(env);
		free_ast(ast);
		free_tokens(tokens);
		exit(1);// creo q esto puede dar problemas cuando se ejecuten minis dentro de minis
	}
}
