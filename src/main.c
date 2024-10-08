/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/08 17:22:15 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_input(char *input, char **envp)
{
	t_token	*tokens;

	tokens = lexer(input);
	parsing(tokens);
	if (ft_strcmp(input, "env") == 0)
	{
		while (*envp)
			printf("%s\n", *envp++);
	}
}

int	main(int argc, char **argv, char **envp)
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
				handle_input(input, envp);
			else
				return (0);
			rl_on_new_line();
		}
	}
	printf(USAGE_ERROR);
	return (1);
}
