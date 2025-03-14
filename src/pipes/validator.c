/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:53:34 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/14 16:56:17 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*access_absolute(char *path)
{
	int		fd_dir1;
	char	*comand_ok;

	fd_dir1 = access(path, X_OK);
	if (fd_dir1 == -1)
	{
		printf("megashell: %s: No such file or directory\n", path);
		return (NULL);
	}
	comand_ok = ft_strdup(path);
	return (comand_ok);
}

char	*access_validate(char **path, char *comand)
{
	char	*dir1;
	int		fd_dir1;
	int		x;

	x = 0;
	fd_dir1 = -1;
	while (path[x] || fd_dir1 == 0)
	{
		dir1 = ft_strjoin_cmd(path[x], comand);
		fd_dir1 = access(dir1, X_OK);
		if (fd_dir1 == 0)
			return (dir1);
		free(dir1);
		x++;
	}
	if (fd_dir1 == -1)
	{
		printf("%s: command not found\n", comand);
		exit(127);
	}
	return (NULL);
}

void	validate_comand(char **comand_splited)
{
	printf("\t--- Error ---\nComand empty\n");
	free_matrix(comand_splited);
	exit(1);
}

char	*command_with_space(char *comand)
{
	char	**comand_splited;
	char	*result;

	comand_splited = ft_split(comand, ' ');
	result = access_absolute(comand_splited[0]);
	free_matrix(comand_splited);
	return (result);
}

char	*load_param(char **path, char *comand)
{
	char	**comand_splited;
	char	*result;

	if (path[0] == NULL && !ft_strchr(comand, '/'))
		result = path_error();
	else if (path[0] == NULL && ft_strchr(comand, '/'))
		result = access_absolute(comand);
	else if (ft_strchr(comand, '/'))
	{
		if (ft_strchr(comand, ' '))
			result = command_with_space(comand);
		else
			result = access_absolute(comand);
	}
	else if (ft_strchr(comand, ' '))
	{
		comand_splited = ft_split(comand, ' ');
		if (comand_splited[0] == NULL)
			validate_comand(comand_splited);
		result = access_validate(path, comand_splited[0]);
		free_matrix(comand_splited);
	}
	else
		result = access_validate(path, comand);
	return (result);
}
