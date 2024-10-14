/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/10 20:47:43 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_input(char *input, char **env)
{
	t_token	*tokens;

	tokens = lexer(input);
	parsing(tokens);
	if (env && env[0])
		built_switch(env, input, tokens);
	// if (env && env[0])
	// 	have_env(env, input);
	// else if (ft_strchr(input, '/') && ft_strchr(input, '/'))
	// 	tramited("", input, env);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			input = readline("$megashell> ");
			add_history(input);
			if (input != NULL)
				handle_input(input, env);
			else
				return (0);
			rl_on_new_line();
		}
	}
	printf(USAGE_ERROR);
	return (1);
}
