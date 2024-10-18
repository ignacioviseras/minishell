/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/19 01:35:26 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int flags_validator(char *flags, char *command_flags)
{
    int i;
	int j;
    int valid_flag;
    char **cmd_flags_splited;

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
            return (free(cmd_flags_splited), i);
    }
    return (free(cmd_flags_splited), 0);
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
	if (ft_charcmp(tokens->next->value[0], '-') == 0)
	{
		x = flags_validator(tokens->next->value, "L P");
		if (x == 0)
			printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
		else
			printf("bash: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n", \
				tokens->next->value[x]);
	}
}

void cd_actions(t_token *tokens)
{
	int x;

	if (ft_charcmp(tokens->next->value[0], '-') == 0)
	{
		x = flags_validator(tokens->next->value, "L P");
		if (x == 0)
			printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
		else
		{
			printf("bash: cd: -%c: invalid option\ncd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", \
			tokens->next->value[x]);
		}
		x++;
	}
	else if (chdir(tokens->next->value) != 0)
		printf("bash: cd: %s: No such file or directory\n", tokens->next->value);
}

/*
	creo q no necesito los ft_strcmp(tokens->value, "cd") == 0
 */
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
	if (ft_strcmp(tokens->value, "cd") == 0 && (tokens->next == NULL || ft_strcmp(tokens->next->value, "~") == 0) )
	{
		if (chdir(home) != 0)
			perror("chdir");
	}
	else if (ft_strcmp(tokens->value, "cd") == 0 && tokens->next->value)
		cd_actions(tokens);
	else if (tokens->next != NULL && tokens->next->next != NULL)
	{
		if (ft_strcmp(tokens->value, "cd") == 0 && tokens->next->next->value)
			printf("bash: cd: too many arguments\n");
	}
}

void command_env(char **env, t_token *tokens)
{
	int	x;

	x = 0;
	if (tokens->next == NULL)
	{
		while (env[x])
		{
			printf("%s\n", env[x]);
			x++;
		}
		return;
	}
	if (ft_charcmp(tokens->next->value[0], '-') == 0)
	{
		x = flags_validator(tokens->next->value, "i 0 u C S v");
		if (x == 0)
			printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
		else
			printf("env: invalid option -- '%c'\nTry 'env --help' for more information.\n", \
				tokens->next->value[x]);
	}
}

void built_switch(char **env, char *find, t_token *tokens)
{
	char **command;

	command = ft_split(find, ' ');
	if (ft_strcmp(command[0], "pwd") == 0)
		command_pwd(tokens);
	else if (ft_strcmp(command[0], "env") == 0)
		command_env(env, tokens);
	else if (ft_strcmp(command[0], "cd") == 0)
		command_cd(tokens);
	// else if (ft_strcmp(find, "echo") == 0)
	// 	command_echo(tokens);
	else if (ft_strcmp(find, "clear") == 0)
		printf("\033[2J\033[H");
	free_matrix(command);
}
