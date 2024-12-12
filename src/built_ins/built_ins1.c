/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/11 19:43:32 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int flags_validator(char *flags, char *command_flags)
{
	int i;
	int j;
	int valid_flag;
	char **cmd_flags_splited;

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
				break;
			}
		}
		if (!valid_flag)
			return (free_matrix(cmd_flags_splited), i);
	}
	return (free_matrix(cmd_flags_splited), 0);
}

char		*get_home(char *pwd)
{
	int x;
	int slash;
	char *home;

	x = 0;
	slash = 0;
	while (pwd[x] != '\0')
	{
		if (slash == 3)
			break;
		if (pwd[x] == '/')
			slash++;
		x++;
	}
	if (slash == 3)
		x = x-1;	
	home = ft_substr(pwd, 0, x);
	return (home);
}

void command_pwd(t_token *tokens)
{
	int x;

	if (tokens->next == NULL)
	{
		char cwd[4096];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		return;
	}
	if (ft_charcmp(tokens->flags[0], '-') == 0)
	{
		x = flags_validator(tokens->flags, "L P");
		if (x == 0)
			printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
		else
			printf("bash: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n", \
				tokens->flags[x]);
	}
}

void cd_actions(t_token *tokens)
{
	int x;

	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
		{
			x = flags_validator(tokens->flags, "L P");
			if (x == 0)
				printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
			else
			{
				printf("bash: cd: -%c: invalid option\ncd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", \
				tokens->flags[x]);
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
	if (ft_strcmp(tokens->cmd, "cd") == 0 && (tokens->args == NULL || ft_strcmp(tokens->args, "~") == 0) )
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
			printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
		else
			printf("env: invalid option -- '%c'\nTry 'env --help' for more information.\n", \
				tokens->flags[x]);
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
		command_pwd(tokens);
	else if (ft_strcmp(cleaned, "env") == 0)
		command_env(tokens, env);
	else if (ft_strcmp(cleaned, "cd") == 0)
		command_cd(tokens);
	else if (ft_strcmp(cleaned, "echo") == 0)
		command_echo(tokens);
	else if (ft_strcmp(cleaned, "export") == 0)
	{
		free(cleaned);
		command_export(tokens, env);
	}
	else if (ft_strcmp(cleaned, "unset") == 0)
		command_unset(tokens, env);
	else if (ft_strcmp(cleaned, "clear") == 0)
		command_clear(tokens);
	else if (ft_strcmp(cleaned, "exit") == 0)
	{
		free_env(env);
		free_ast(ast);
		free_tokens(tokens);
		exit(1);// creo q esto puede dar problemas cuando se ejecuten minis dentro de minis
	}
}
