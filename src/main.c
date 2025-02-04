/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/04 19:17:36 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* void	print_redirects(t_list *redirects, char *type)
{
	t_redirect_file	*redirection;

	printf("%s:\n", type);
	while (redirects)
	{
		redirection = (t_redirect_file *)redirects->content;
		if (redirection)
			printf("Value: %s, Type: %d\n", redirection->value,
				redirection->type);
		redirects = redirects->next;
	}
}

void	print_ast(t_ast *node, int depth)
{
	t_token	*data;
	t_list	*infiles;
	t_list	*outfiles;
	int		i;

	if (node == NULL)
		return ;
	data = (t_token *)(node->data);
	i = 0;
	while (i < depth)
	{
		printf("	");
		i++;
	}
	printf("Node full_cmd: '%s', ", data->full_cmd);
	printf("Node cmd: '%s', ", data->cmd);
	printf("node args: '%s', ", data->args);
	printf("node flags: '%s', ", data->flags);
	printf("Node type: '%d'\n", data->type);
	outfiles = data->outfiles;
	infiles = data->infiles;
	print_redirects(outfiles, "Outfiles");
	print_redirects(infiles, "Infiles");
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
} */

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
		before_create_env(&env, envp);
		while (1)
		{
			handle_signals();
			input = readline("megashell$ ");
			add_history(input);
			if (input != NULL)
				handle_input(env, input);
			else
			{
				printf("exit\n");
				return (free_env(env), 0);
			}
			rl_on_new_line();
			free(input);
		}
	}
	printf(USAGE_ERROR);
	return (1);
}
