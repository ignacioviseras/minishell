/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/01 16:02:22 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	create_env(t_env *env, char **envp)
{
	t_env	*aux;

	aux = env;
	while (envp && *envp)
	{
		env->key = ft_substr(*envp, 0, findchar(*envp, '='));
		env->value = ft_substr(*envp, findchar(*envp, '=') + 1, findchar(*envp,
					'\0'));
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

void	print_ast(t_ast *node, int depth)
{
	t_token			*data;
	t_redirect_file	*redirection;
	t_list			*infiles;
	t_list			*outfiles;

	if (node == NULL)
		return ;
	data = (t_token *)(node->data);
	for (int i = 0; i < depth; i++)
		printf("	");
	printf("Node full_cmd: '%s', ", data->full_cmd);
	printf("Node cmd: '%s', ", data->cmd);
	printf("node args: '%s', ", data->args);
	printf("node flags: '%s', ", data->flags);
	printf("Node type: '%d'\n", data->type);
	outfiles = data->outfiles;
	infiles = data->infiles;
	printf("Outfiles:\n");
	while (outfiles)
	{
		redirection = (t_redirect_file *)outfiles->content;
		if (redirection)
			printf("Value: %s, Type: %d\n", redirection->value,
					redirection->type);
		outfiles = outfiles->next;
	}
	printf("Infiles:\n");
	while (infiles)
	{
		redirection = (t_redirect_file *)infiles->content;
		if (redirection)
			printf("Value: %s, Type: %d\n", redirection->value,
					redirection->type);
		infiles = infiles->next;
	}
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

int	count_ast_nodes(t_ast *node)
{
	t_token	*data;

	if (node == NULL)
		return (0);
	data = (t_token *)(node->data);
	if (data != NULL && data->type == TOKEN_PIPE)
		return (count_ast_nodes(node->left) + count_ast_nodes(node->right));
	return (1 + count_ast_nodes(node->left) + count_ast_nodes(node->right));
}

void	handle_input(t_env *env, char *input)
{
	t_token		*tokens;
	t_ast		*ast;
	t_params	p;

	tokens = lexer(input);
	ast = parsing(tokens, env);
	// print_ast(ast, 0);
	p.total_cmds = count_ast_nodes(ast);
	p.env = init_env(env);
	init_pipes(ast, &p, env);
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
			if (input != NULL)
				handle_input(env, input);
			else
				return (free_env(env), 0);
			rl_on_new_line();
			free(input);
		}
	}
	printf(USAGE_ERROR);
	return (1);
}
