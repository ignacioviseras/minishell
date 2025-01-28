/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/28 18:03:30 by drestrep         ###   ########.fr       */
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
	printf("Node full_cmd: '%s', ", data->full_cmd);
	printf("Node cmd: '%s', ", data->cmd);
	printf("node args: '%s', ", data->args);
	printf("node flags: '%s', ", data->flags);
	printf("Node type: '%d'\n", data->type);
	t_redirect_file	*redirection;
	t_list			*infiles;
	t_list			*outfiles;
	outfiles = data->outfiles;
	infiles = data->infiles;
	printf("Outfiles:\n");
	while (outfiles)
	{
		redirection = (t_redirect_file *)outfiles->content;
		if (redirection)
			printf("Value: %s, Type: %d\n", redirection->value, redirection->type);
		outfiles = outfiles->next;
	}
	printf("Infiles:\n");
	while (infiles)
	{
		redirection = (t_redirect_file *)infiles->content;
		if (redirection)
			printf("Value: %s, Type: %d\n", redirection->value, redirection->type);
		infiles = infiles->next;
	} 
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
	if (data != NULL && data->type == TOKEN_PIPE)
		return (count_ast_nodes(node->left) + count_ast_nodes(node->right));
	// if (data != NULL && (ft_strcmp(data->cmd, "<<") == 0 || ft_strcmp(data->cmd, "<") == 0 ||
	// 					 ft_strcmp(data->cmd, ">") == 0 || ft_strcmp(data->cmd, ">>") == 0))
	// 	return (count_ast_nodes(node->right)); // ignora lso << >> < >

	return (1 + count_ast_nodes(node->left) + count_ast_nodes(node->right));
}

void	handle_input(t_env *env, char *input)
{
	t_token	*tokens;
	t_ast	*ast;
	t_params p;

	tokens = lexer(input);
	ast = parsing(tokens, env);
	/* int	i = 0;
	while (tokens)
	{
		printf("Token %d:\n", i++);
		printf("	Cmd: %s\n", tokens->cmd);
		printf("	Flags: %s\n", tokens->flags);
		printf("	Args: %s\n", tokens->args);

		t_redirect_file	*redirection;
		t_list			*infiles;
		t_list			*outfiles;

		outfiles = tokens->outfiles;
		infiles = tokens->infiles;

		printf("	Outfiles:\n");
		while (outfiles)
		{
			redirection = (t_redirect_file *)outfiles->content;
			if (redirection)
				printf("		Value: %s, Type: %d\n", redirection->value, redirection->type);
			outfiles = outfiles->next;
		}
		printf("	Infiles:\n");
		while (infiles)
		{
			redirection = (t_redirect_file *)infiles->content;
			if (redirection)
				printf("		Value: %s, Type: %d\n", redirection->value, redirection->type);
			infiles = infiles->next;
		}
		tokens = tokens->next;
	}
	exit(0); */
	print_ast(ast, 0);
	p.total_cmds = count_ast_nodes(ast);
	printf("numero de comandos '%d'\n", p.total_cmds);
	p.env = init_env(env);
	init_pipes(ast, &p, env);
	free_tokens(tokens);
	free_ast(ast);
}

void	add_path(t_env **env)
{
	t_env	*aux;
	t_env	*new_node;
	char	*value;

	value = "/usr/sbin:/usr/bin:/sbin:/bin:"
			"/usr/games:/usr/local/games:/usr/lib/wsl/lib";
	aux = *env;
	while (aux)
	{
		if (ft_strcmp(aux->key, "PATH") == 0)
			return;
		aux = aux->next;
	}
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return;
	new_node->key = ft_strdup("PATH");
	new_node->value = ft_strdup(value);
	new_node->hide = 0;
	new_node->next = *env;
	*env = new_node;
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
		add_path(&env);
		//add path en caso de no tener por env -i
		while (1)
		{
			// handle_signals();
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
