/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/09 20:47:15 by igvisera         ###   ########.fr       */
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

void pwd(char **env)
{
	char *pwd;
	
	pwd = env_finder(env, "PWD");
	printf("%s\n", pwd);
}

// void cd()
// {
	
// }

// void env()
// {
	
// }

void built_switch(char **env, char *find)
{
	if (ft_strcmp(find, "pwd") == 0)
		pwd(env);
	// else if (ft_strcmp(find, "cd"))
	// 	cd(env);
	// else if (ft_strcmp(find, "env"))
	// 	env(env);
	
}