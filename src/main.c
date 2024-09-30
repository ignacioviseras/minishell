/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/09/30 15:42:04 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_input(t_input *input, char **envp)
{
	t_token	*tokens;
	int		i;

	i = 1;
	tokens = lexer(input->line);
	while (tokens != NULL)
	{
		printf("Token %i: %s\n", i++, tokens->value);
		tokens = tokens->next;
	}
	return ;
	if (ft_strcmp(input->line, "env") == 0)
	{
		while (*envp)
			printf("%s\n", *envp++);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_input	input;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			input.line = readline("$megashell> ");
			add_history(input.line);
			if (input.line != NULL)
				handle_input(&input, envp);
			else
				return (0);
			rl_on_new_line();
		}
	}
	printf(USAGE_ERROR);
	return (1);
}
