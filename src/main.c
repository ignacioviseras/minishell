/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/07 18:45:24 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_redirects(t_list *redirects, char *type)
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

// void process_heredocs_in_ast(t_ast *node, t_env *env)
// {
//     t_token         *data;
//     t_list          *tmp;
//     t_redirect_file *redir;
//     char            *temp_filename;
//     int             fd;
//     char            *line;

//     if (!node)
//         return;
//     data = (t_token *)node->data;
//     if (data->infiles)
//     {
//         tmp = data->infiles;
//         while (tmp)
//         {
//             redir = (t_redirect_file *)tmp->content;
//             if (redir && redir->type == HEREDOC)
//             {
//                 temp_filename = ft_strdup(".heredoc.tmp");
//                 fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//                 if (fd < 0)
//                 {
//                     perror("open temp heredoc");
//                     exit(EXIT_FAILURE);
//                 }
//                 while ((line = readline("> ")) != NULL)
//                 {
//                     if (ft_strcmp(line, redir->value) == 0)
//                     {
//                         free(line);
//                         break;
//                     }
//                     write_to_heredoc(fd, line, env);
//                 }
//                 close(fd);
//                 redir->type = INFILE;
//                 free(redir->value);
//                 redir->value = ft_strdup(temp_filename);
//                 free(temp_filename);
//             }
//             tmp = tmp->next;
//         }
//     }
//     process_heredocs_in_ast(node->left, env);
//     process_heredocs_in_ast(node->right, env);
// }

static void process_single_heredoc(t_redirect_file *redir, t_env *env)
{
    char *temp_filename;
    int fd;
    char *line;

    temp_filename = ft_strdup(".heredoc.tmp");
    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open temp heredoc");
        exit(EXIT_FAILURE);
    }
    while ((line = readline("> ")) != NULL)
    {
        if (ft_strcmp(line, redir->value) == 0)
        {
            free(line);
            break;
        }
        write_to_heredoc(fd, line, env);
    }
    close(fd);
    redir->type = INFILE;
    free(redir->value);
    redir->value = ft_strdup(temp_filename);
    free(temp_filename);
}

static void process_heredoc_list(t_list *list, t_env *env)
{
    t_redirect_file *redir;

    while (list)
    {
        redir = (t_redirect_file *)list->content;
        if (redir && redir->type == HEREDOC)
            process_single_heredoc(redir, env);
        list = list->next;
    }
}

void process_heredocs_in_ast(t_ast *node, t_env *env)
{
    t_token *data;

    if (!node)
        return;
    data = (t_token *)node->data;
    if (data->infiles)
        process_heredoc_list(data->infiles, env);
    process_heredocs_in_ast(node->left, env);
    process_heredocs_in_ast(node->right, env);
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
	process_heredocs_in_ast(ast, env);
	execute_ast(ast, &p, env, -1);
	free_matrix(p.env);
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
