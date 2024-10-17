/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/17 18:10:45 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

void	create_env(t_env *env, char **envp)
{
	t_env	*aux;

	aux = env;
	while (envp && *envp)
	{
		env->key= ft_substr(*envp, 0, ft_strchr(*envp, '='));
		env->value = ft_substr(*envp, ft_strchr(*envp, '=') + 1, ft_strchr(*envp, '\0'));
		env->next = malloc(sizeof(t_env)); 
		env = env->next;
		envp++;
	}
	env = aux;
	while (env && env->next)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	handle_input(t_env *env, char *input)
{
	t_token	*tokens;
	t_ast	*ast;

	tokens = lexer(input);
	while (tokens)
		ast = parsing(&tokens, env);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*input;

	atexit(leaks);
	(void)argv;
	if (argc == 1)
	{
		env = malloc(sizeof(env));
		create_env(env, envp);
		return (0);
		while (1)
		{
			input = readline("$megashell> ");
			add_history(input);
			if (input != NULL)
				handle_input(env, input);
			else
				return (0);
			rl_on_new_line();
		}
	}
	printf(USAGE_ERROR);
	return (1);
}
