/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/24 00:19:41 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* void	leaks(void)
{
	system("leaks -q minishell");
} */

/*
 *  Transforms the environment into a linked list.
 *  TO DO: No sé qué hacer si envp == NULL.
 */
void	create_env(t_env *env, char **envp)
{
	t_env	*aux;

	aux = env;
	while (envp && *envp)
	{
		env->key = ft_substr(*envp, 0, ft_charseach(*envp, '='));
		env->value = ft_substr (*envp, ft_charseach(*envp, '=') \
		+ 1, ft_charseach(*envp, '\0'));
		if (*(envp + 1))
			env->next = ft_malloc(sizeof(t_env));
		else
			env->next = NULL;
		env = env->next;
		envp++;
	}
	env = aux;
	/* while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	} */
}

// Printea el árbol de forma recursiva, cada tab es un nivel más profundo.
// Cambiar valores del printf para ver más variables :D
void	print_ast(t_ast *node, int depth)
{
	if (node == NULL)
		return ;
	t_token *data = (t_token *)(node->data);
	for (int i = 0; i < depth; i++)
		printf("	");
	printf("Node cmd: '%s', ", data->cmd);
	printf("node args: '%s'\n", data->args);
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

void	handle_input(t_env *env, char *input)
{
	t_token	*tokens;
	t_ast	*ast;

	tokens = lexer(input);
	ast = parsing(tokens, env);
	print_ast(ast, 0);
	if (tokens && ft_strcmp(tokens->cmd, "exit") == 0)
	{
		free_tokens(ast);
		free_ast(ast);
		//free_env(env);
		exit(1);
	}
	if (env)
		build_switch(env, input);
	free_tokens(ast);
	free_ast(ast);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*input;

	//atexit(leaks);
	(void)argv;
	if (argc == 1)
	{
		env = ft_malloc(sizeof(t_env));
		create_env(env, envp);
		while (1)
		{
			input = readline("$megashell> ");
			add_history(input);
			if (input != NULL)
				handle_input(env, input);
			else
			{
				free_env(env);
				return (0);
			}
			rl_on_new_line();
			free(input);
		}
	}
	printf(USAGE_ERROR);
	return (1);
}
