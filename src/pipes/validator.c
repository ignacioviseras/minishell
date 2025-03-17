/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:53:34 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/17 21:22:35 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*access_absolute(char *path)
{
	int		fd_dir1;
	char	*command_ok;

	fd_dir1 = access(path, X_OK);
	if (fd_dir1 == -1)
	{
		printf("megashell: %s: No such file or directory\n", path);
		return (NULL);
	}
	command_ok = ft_strdup(path);
	return (command_ok);
}

char	*access_validate(char **path, char *command)
{
	char	*dir1;
	int		fd_dir1;
	int		x;

	x = 0;
	fd_dir1 = -1;
	while (path[x] || fd_dir1 == 0)
	{
		dir1 = ft_strjoin_cmd(path[x], command);
		fd_dir1 = access(dir1, X_OK);
		if (fd_dir1 == 0)
			return (dir1);
		free(dir1);
		x++;
	}
	if (fd_dir1 == -1)
	{
		printf("%s: command not found\n", command);
		exit(127);
	}
	return (NULL);
}

void	validate_command(char **command_splited)
{
	printf("\t--- Error ---\ncommand empty\n");
	free_matrix(command_splited);
	exit(1);
}

char	*command_with_space(char *command)
{
	char	**command_splited;
	char	*result;

	command_splited = ft_split(command, ' ');
	result = access_absolute(command_splited[0]);
	free_matrix(command_splited);
	return (result);
}

char	*load_param(char **path, char *command)
{
	char	**command_splited;
	char	*result;

	if (path[0] == NULL && !ft_strchr(command, '/'))
		result = path_error();
	else if (path[0] == NULL && ft_strchr(command, '/'))
		result = access_absolute(command);
	else if (ft_strchr(command, '/'))
	{
		if (ft_strchr(command, ' '))
			result = command_with_space(command);
		else
			result = access_absolute(command);
	}
	else if (ft_strchr(command, ' '))
	{
		command_splited = ft_split(command, ' ');
		if (command_splited[0] == NULL)
			validate_command(command_splited);
		result = access_validate(path, command_splited[0]);
		free_matrix(command_splited);
	}
	else
		result = access_validate(path, command);
	return (result);
}
