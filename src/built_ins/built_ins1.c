/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/16 20:23:53 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

// char *env_finder(char **env, char *find)
// {
// 	int	x;
// 	char *env_path;
// 	char *found;

// 	x = 0;
// 	env_path = ft_strjoin(ft_str_toupper(find), "=");
// 	while (env[x])
// 	{
// 		if (ft_strncmp(find, env[x], ft_strlen(find)) == 0)
// 		{
// 			found = env[x] + ft_strlen(env_path) - 1;
// 			free(env_path); 
// 			return(found);
// 		}
// 		x++;
// 	}
// 	return (free(env_path), NULL);
// }

// int flags_validator(char *flags, char *command_flags)
// {
// 	int x;
// 	char **flags_splited;
// 	char **cmd_flags_splited;
	
// 	// cd -asddpi
// 	// 0. 'asddpi'
// 	// 1. '(null)'

// 	// flags_splited = ft_split(flags+1, ' ');
// 	// flags+1;
// 	x = 1;
// 	flags_splited = ft_calloc(ft_strlen(flags+1), sizeof(char *));
// 	cmd_flags_splited = ft_split(command_flags, ' ');
// 	while (flags[x] != '\0')
// 	{
// 		flags_splited[x][0] = ft_strdup((char *)flags[x]);
// 		x++;
// 	}
	
// 	// if ()
// 	// {

// 	// }
	
// 	printf("0. '%s'\n", flags_splited[1]);
// 	printf("1. '%s'\n", flags_splited[2]);
// 	printf("2. '%s'\n", flags_splited[3]);
// 	printf("3. '%s'\n", flags_splited[4]);
// 	// while (flags_splited[x])
// 	// {
// 		// while (cmd_flags_splited[i])
// 		// {
// 		// 	i++;
// 		//
// 		// }		
// 	// 	x++
// 	// }
	
// 	free(flags_splited);
// 	free(cmd_flags_splited);
// 	return (0);//existen las flags
// }

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

void command_pwd()
{
	// uso 4096 como estandar de tamaño pq no el limits no me pilla PATH_MAX
	char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
	//necestio un perror?? por si no funicona?
}

/*
	creo q no necesito los ft_strcmp(tokens->value, "cd") == 0
 */
void command_cd(t_token *tokens)
{
	if (tokens == NULL)
		return;
	static char *home;
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
	else if (tokens->next != NULL && tokens->next->next != NULL)
	{
		if (ft_strcmp(tokens->value, "cd") == 0 && tokens->next->next->value)
			printf("bash: cd: too many arguments\n");
	}
	else if (ft_strcmp(tokens->value, "cd") == 0 && tokens->next->value)
	{
		// if (flags_validator(tokens->next->value, "L P") == 0)
		// 	printf("son correctas las flags\n");
/*
	en caso de pasar una flag erronea tengo q poner esto
	cd -z src 
	cd: string not in pwd: -z

	si la flag existe dar un mensaje de que no esta implementado L P
*/
		if (chdir(tokens->next->value) != 0)
			printf("bash: cd: %s: No such file or directory\n", tokens->next->value);
	}
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
	printf("find '%s'\n", find);
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
