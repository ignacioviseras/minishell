/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/10 14:23:35 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		env->key = ft_substr(*envp, 0, findchar(*envp, '='));
		env->value = ft_substr (*envp, findchar(*envp, '=') \
		+ 1, findchar(*envp, '\0'));
		env->hide = 0;
		if (*(envp + 1))
			env->next = ft_malloc(sizeof(t_env));
		else
			env->next = NULL;
		env = env->next;
		envp++;
	}
	env = aux;
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
	printf("node args: '%s', ", data->args);
	printf("node flags: '%s'\n", data->flags);
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

int	count_ast_nodes(t_ast *node)
{
	t_token *data;
// tengo q cambiar los trcmp por los TYPE y el tipo de dato pero q PUTA pereza
	if (node == NULL)
		return 0;
	data = (t_token *)(node->data);
	if (data != NULL && (ft_strcmp(data->cmd, "|") == 0))
		return (count_ast_nodes(node->left) + count_ast_nodes(node->right));
	if (data != NULL && (ft_strcmp(data->cmd, "<<") == 0 || ft_strcmp(data->cmd, "<") == 0 ||
						 ft_strcmp(data->cmd, ">") == 0 || ft_strcmp(data->cmd, ">>") == 0))
		return (count_ast_nodes(node->right)); // ignora lso << >> < >

	return (1 + count_ast_nodes(node->left) + count_ast_nodes(node->right));
}

void	handle_input(t_env *env, char *input)
{
	t_token	*tokens;
	t_ast	*ast;
	t_params p;

	tokens = lexer(input);
	ast = parsing(tokens, env);
	print_ast(ast, 0);
	p.total_cmds = count_ast_nodes(ast);
	//printf("numero de comandos %d\n", p.total_cmds);
	p.env = init_env(env);
	init_pipes(ast, &p);
	build_switch(env, ast, tokens);
	free_tokens(tokens);
	free_ast(ast);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*input;

	(void)argv;
	if (argc == 1)
	{
		env = ft_malloc(sizeof(t_env));
		create_env(env, envp);
		while (1)
		{
			handle_signals();
			input = readline("megashell$ ");
			add_history(input);
			if (input != NULL){
				//dprintf(2, "estas accediendo aqui??\n");
				handle_input(env, input);
			}
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
