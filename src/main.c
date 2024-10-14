/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/14 18:11:46 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

void built_switch(t_ast *ast, char **env)
{
	(void)ast;
	(void)env;
}

void	handle_input(char *input, char **env)
{
	t_token	*tokens;
	t_ast	*ast;

	tokens = lexer(input);
	ast = parsing(&tokens);
	 return ;
	if (env && env[0])
		built_switch(ast, env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	atexit(leaks);
	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			input = readline("$megashell> ");
			add_history(input);
			if (input != NULL)
				handle_input(input, envp);
			else
				return (0);
			rl_on_new_line();
		}
	}
	printf(USAGE_ERROR);
	return (1);
}
