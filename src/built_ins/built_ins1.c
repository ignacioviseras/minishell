/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/14 14:00:32 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

char *env_finder(char **env, char *find)
{
	int	x;
	char *env_path;
	char *found;

	x = 0;
	env_path = ft_strjoin(ft_str_toupper(find), "=");
	while (env[x])
	{
		if (ft_strncmp(find, env[x], ft_strlen(find)) == 0)
		{
			found = env[x] + ft_strlen(env_path) - 1;
			free(env_path); 
			return(found);
		}
		x++;
	}
	return (free(env_path), NULL);
}

void command_pwd()
{
	// uso 4096 como estandar de tamaño pq no el limits no me pilla PATH_MAX
	char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
	//necestio un perror?? por si no funicona?
}

void command_cd(t_token *tokens)
{
	if (tokens == NULL)
		return;
	if (ft_strcmp(tokens->value, "cd") == 0 && tokens->next == NULL)
	{
		if (chdir("~") != 0) //mirar como hacer esto bn
			perror("chdir");
	}
	else if (tokens->next != NULL && tokens->next->next != NULL)
	{
		if (ft_strcmp(tokens->value, "cd") == 0 && tokens->next->next->value)
			printf("bash: cd: too many arguments\n");
	}
	else if (ft_strcmp(tokens->value, "cd") == 0 && tokens->next->value)
		if (chdir(tokens->next->value) != 0)
			printf("bash: cd: %s: No such file or directory\n", tokens->next->value);
}

void command_env(char **env)
{
	int	x;

	x = 0;
	while (env[x])
	{
		printf("%s\n", env[x]);
		x++;
	}
}

void built_switch(char **env, char *find, t_token *tokens)
{
	// printf("1 '%s'\n", tokens->next->value);
	printf("find '%s'\n", find);
	printf("accde\n");
	char **command;
	command = ft_split(find, ' ');
	if (ft_strcmp(command[0], "pwd") == 0)
		command_pwd();
	else if (ft_strcmp(command[0], "env") == 0)
		command_env(env);
	else if (ft_strcmp(command[0], "cd") == 0)
		command_cd(tokens);
	else if (ft_strcmp(find, "clear") == 0)
		printf("\033[2J\033[H");
	free_matrix(command);
}
