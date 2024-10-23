/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/23 11:47:02 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_input(char *input, t_envi *envi)
{
	t_token	*tokens;

	tokens = lexer(input);
	parsing(tokens);
	//mirar control de errores por si no hay env
	// if (env && env[0])
	// {
		built_switch(envi, tokens);
    	// print_envi(envi);
	// }
	// if (env && env[0])
	// 	have_env(env, input);
	// else if (ft_strchr(input, '/') && ft_strchr(input, '/'))
	// 	tramited("", input, env);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_envi	*envi;

	(void)argv;
	if (argc == 1)
	{
		envi = NULL;
		init_env(env, &envi);
		while (1)
		{
			input = readline("$megashell> ");
			add_history(input);
			if (input != NULL)
				handle_input(input, envi);
			else
			{
				free_env(envi);
				return (0);
			}
			rl_on_new_line();
			free(input);
		}
	}
	printf(USAGE_ERROR);
	return (1);
}
