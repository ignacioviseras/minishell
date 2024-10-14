/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:43:00 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/12 16:12:51 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

// void	have_env(char **env, char *argv)
// {
// 	int	x;

// 	x = 0;
// 	while (env[x])
// 	{
// 		if (ft_strncmp("PATH=", env[x], 5) == 0)
// 			tramited(env[x] + 5, argv, env);
// 		x++;
// 	}
// }


// int	tramited(char *path, char *arguments, char **env)
// {
// 	char		**dir;
// 	t_params	p;

// 	dir = ft_split(path + 5, ':');
// 	p.file1 = arguments[1];
// 	p.file2 = arguments[4];
// 	dprintf(2, "monta '%s'\n", arguments[3]);

// 	p.comand_path1 = load_param(dir, arguments[2]);
// 	p.comand_path2 = load_param(dir, arguments[3]);
// 	p.comand1 = split_formated(arguments[2], ' ');
// 	p.comand2 = split_formated(arguments[3], ' ');
// 	free_matrix(dir);
// 	if ((p.comand_path1 != NULL) && (p.comand_path2 != NULL))
// 		initpipe(&p, env);
// 	else
// 	{
// 		free(p.comand_path1);
// 		free(p.comand_path2);
// 		free_matrix(p.comand1);
// 		free_matrix(p.comand2);
// 		exit(1);
// 	}
// 	return (0);
// }