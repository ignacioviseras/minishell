/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:41 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/24 00:20:34 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

char *env_finder(t_env *env, char *find)
{
	while (env)
	{
		if (ft_strncmp(find, env->key, ft_strlen(find)) == 0)
			return(env->value);
		env = env->next;
	}
	return (NULL);
}

void pwd(t_env *env)
{
	char *pwd;
	
	pwd = env_finder(env, "PWD");
	printf("%s\n", pwd);
}


void build_switch(t_env *env, char *find)
{
	if (ft_strcmp(find, "pwd") == 0)
		pwd(env);
	// else if (ft_strcmp(find, "cd"))
	// 	cd(env);
	// else if (ft_strcmp(find, "env"))
	// 	env(env);
	
}
