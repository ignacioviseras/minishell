/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:34:57 by igvisera          #+#    #+#             */
/*   Updated: 2025/03/17 21:25:18 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_env_flags(t_token *tokens)
{
	int	x;

	x = flags_validator(tokens->flags, "i 0 u C S v");
	if (x == 0)
	{
		printf("flags are not implemented\n");
		g_exit_status = 777;
	}
	else
	{
		printf("env: invalid option -- '%c'\n", tokens->flags[x]);
		printf("Try 'env --help' for more information.\n");
		g_exit_status = 125;
	}
}

void	print_env(t_env *env, int flag)
{
	int	i;

	i = 1;
	if (!env)
		printf("Empty\n");
	while (env)
	{
		if (flag == 1)
		{
			if (env->value != NULL)
				printf("%s=\"%s\"\n", env->key, env->value);
			else
				printf("%s\n", env->key);
		}
		else if (env->hide == 0)
		{
			if (env->value != NULL && ft_strcmp(env->value, "\0") != 0)
				printf("%s=%s\n", env->key, env->value);
			else if (ft_strcmp(env->value, "\0") != 0)
				printf("%s\n", env->key);
		}
		env = env->next;
		i++;
	}
}

void	command_env(t_token *tokens, t_env *envi)
{
	if (tokens->args != NULL && ft_strcmp(tokens->args, ""))
	{
		printf("env: ‘%s’: No such file or directory\n", tokens->args);
		g_exit_status = 127;
		return ;
	}
	if (tokens->flags == NULL)
	{
		print_env(envi, 0);
		return ;
	}
	if (ft_charcmp(tokens->flags[0], '-') == 0)
		handle_env_flags(tokens);
}
