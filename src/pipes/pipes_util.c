/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:43:00 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/04 21:48:40 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

//------------------------REDIRECCIONES------------------------------

void redirect_input(t_token *data)
{
    int fd;
    fd = open(data->args, O_RDONLY);
    if (fd < 0)
    {
        perror("open input");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, 0) < 0)
    {
        perror("dup2 input");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void redirect_output(t_token *data)
{
    int fd = open(data->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open output");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, 1) < 0) {
        perror("dup2 output");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void redirect_append(t_token *data)
{
    int fd = open(data->args, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("open append");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, 1) < 0) {
        perror("dup2 append");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

int open_heredoc()
{
    int fd_file = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_file < 0)
    {
        perror("open heredoc");
        exit(EXIT_FAILURE);
    }
    return fd_file;
}

void write_heredoc(int fd_file, char *delimiter)
{
    char *buffer;
    ssize_t content;
    ssize_t cnt;

    buffer = NULL;
    while (1)
    {
        buffer = readline("> ");
        if (buffer == NULL || ft_strcmp(buffer, delimiter) == 0)
        {
            free(buffer);
            break;
        }
        if (ft_strlen(buffer) > 0)
        {
            content = write(fd_file, buffer, ft_strlen(buffer));
            if (content < 0)
            {
                perror("write to heredoc file");
                free(buffer);
                exit(EXIT_FAILURE);
            }
            cnt = write(fd_file, "\n", 1);
            if (cnt < 0)
            {
                perror("write to heredoc file");
                free(buffer);
                exit(EXIT_FAILURE);
            }
        }
        free(buffer);
    }
}

void handle_heredoc(t_token *data, t_ast *node)
{
    int fd_file;
    int original_stdin;
    //char *line;

    fd_file = open_heredoc();
    // printf("cmd_args '%s'\n", data->full_cmd);
	// printf("flags '%s'\n", data->flags);
	// printf("cmd '%s'\n", data->cmd);
	// printf("args '%s'\n", data->args);
	printf("type '%d'\n", data->type);
	// printf("nombre de eof '%s'\n", node->right->data);
    if (node->right->data != NULL)
    {
        t_token *data;

        data = (t_token *)(node->right->data);
        write_heredoc(fd_file, data->cmd);

    }
    close(fd_file);
    original_stdin = dup(STDIN_FILENO);
    if (original_stdin < 0)
    {
        perror("dup original stdin");
        exit(EXIT_FAILURE);
    }
    fd_file = open("heredoc.tmp", O_RDONLY);
    if (fd_file < 0)
    {
        perror("open heredoc file");
        exit(EXIT_FAILURE);
    }
    // line = gnl(fd_file);
    // while (line != NULL)
    // {
    //     printf("%s", line);
    //     free(line);
    //     line = gnl(fd_file);
    // }
    
    if (dup2(fd_file, STDIN_FILENO) < 0)
    {
        perror("dup2 heredoc");
        exit(EXIT_FAILURE);
    }
    close(fd_file);
    if (dup2(original_stdin, STDIN_FILENO) < 0)
    {
        perror("restore stdin");
        exit(EXIT_FAILURE);
    }
    close(original_stdin);
}


void handle_redirection(t_ast *node, t_params *p)
{
    t_token *data;

    data = (t_token *)(node->data);
    if (data == NULL)
        return;
    if (ft_strcmp(data->cmd, "<") == 0)
        redirect_input(data);
    else if (ft_strcmp(data->cmd, ">") == 0)
        redirect_output(data);
    else if (ft_strcmp(data->cmd, ">>") == 0)
        redirect_append(data);
    else if (ft_strcmp(data->cmd, "<<") == 0)
    {
        handle_heredoc(data, node);
        execute_node(node->right, p);
    }
        
}
//------------------------------------------------------

void	get_path(char **env, t_params *p, t_token *t)
{
	int	x;

	x = 0;
	while (env[x])
	{
		if (ft_strncmp("PATH=", env[x], 5) == 0)
			tramited(p->env[x] + 5, p, t);
		x++;
	}
	tramited("", p, t);

}

void execute_cmd(t_params *p)
{
    int i;
    
    i = execve(p->cmd_path, p->cmd_exec, p->env);
    if (i < 0)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

int	tramited(char *path, t_params *p, t_token *t)
{
	char		**dir;

	dir = ft_split(path, ':');
	p->cmd_path = load_param(dir, t->full_cmd);
	p->cmd_exec = split_formated(t->full_cmd, ' ');
	free_matrix(dir);
	if (p->cmd_path != NULL)
        execute_cmd(p);
	else
	{
		free(p->cmd_path);
		free_matrix(p->cmd_exec);
		exit(1);//TODO aqui se tendria q liberar todos los daros
	}
	return (0);
}

void dup_read(t_params *p)
{
	int result;

	result = dup2(p->fd[p->fd_index - 2], 0);
	if(result < 0)
	{
		perror("dup2 input");
		exit(EXIT_FAILURE);
	}
}

void dup_write(t_params *p)
{
	int result;

	result = dup2(p->fd[p->fd_index + 1], 1);
	if (result < 0)
	{
		perror("dup2 output");
		exit(EXIT_FAILURE);
	}
}

void init_execute(t_token *data, t_params *p)
{
	if (p->env && p->env[0])
		get_path(p->env, p, data);
	else if (ft_strchr(data->cmd, '/'))
		tramited("", p, data);
	return;
}

void	handle_pipe(t_ast *node, t_params *p)
{
	if (!node)
        return;
	execute_ast(node->left, p);//procesar el nodo recursivamente lado izq
	p->fd_index += 2;//mover index para extemos de los dups
	execute_ast(node->right, p);//procesar el nodo recursivamente lado derch
}

void execute_node(t_ast *node, t_params *p)
{
    t_token *data;
    int pid;
    int i;

    data = (t_token *)(node->data);
    pid = fork();
    if (pid == 0)
    {
        if (p->fd_index != 0)
            dup_read(p);
        if (p->fd_index < 2 * (p->total_cmds - 1))
            dup_write(p);
        i = 0;
        while (i < 2 * p->total_cmds)
        {
            close(p->fd[i]);
            i++;
        }
        if (data && ft_strcmp(data->cmd, "|") == 0)
            handle_pipe(node, p);  // mueve la pipe es para casos dnd las redirect estan por el centro
        else if (data && (ft_strcmp(data->cmd, "<<") == 0 || ft_strcmp(data->cmd, "<") == 0 || 
                           ft_strcmp(data->cmd, ">") == 0 || ft_strcmp(data->cmd, ">>") == 0))
            handle_redirection(node, p);//ejecucion de las redirecciones
        else
            init_execute(data, p);//ejecucion normal
    }
    else if (pid > 0)
    {
        close(p->fd[p->fd_index + 1]);
        waitpid(pid, NULL, 0);
    }
    else 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void execute_ast(t_ast *node, t_params *p)
{
	t_token *data;
    if (node == NULL)
        return;
    data = (t_token *)(node->data);
    if (ft_strcmp(data->cmd, "|") == 0)
		handle_pipe(node, p);//manejo de la pipe
    else if (ft_strcmp(data->cmd, "<<") == 0)
        handle_redirection(node, p);
	else
		execute_node(node, p);//funcionamiento del nodo
}

char *create_char(t_env *env)
{
    char *str;
    char *temp;

    if (!env || !env->key)
        return (NULL);
    str = ft_strdup(env->key);
    if (!str)
        return (NULL);
    if (env->value)
    {
        temp = ft_strjoin(str, "=");
        free(str);
        if (!temp)
            return (NULL);
        str = ft_strjoin(temp, env->value);
        free(temp);
        if (!str)
            return (NULL);
    }
    return (str);
}

int count_env_nodes(t_env *env)
{
    int count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

char **init_env(t_env *env)
{
    char **env_matrix;
    int env_count;
    int x;

    env_count = count_env_nodes(env);
    env_matrix = ft_malloc((env_count + 1) * sizeof(char *));
    if (!env_matrix)
        return (NULL);
    x = 0;
    while (env)
    {
        env_matrix[x] = create_char(env);
        if (!env_matrix[x])
        {
            while (x-- > 0)
                free(env_matrix[x]);
            free(env_matrix);
            return (NULL);
        }
        x++;
        env = env->next;
    }
    env_matrix[x] = NULL;
    return (env_matrix);
}

void init_pipes(t_ast *ast, t_params *p)
{
    int i;
    int resultpipe;

    i = 0;
    p->fd = malloc(2 * p->total_cmds * sizeof(int));
    while (i < p->total_cmds - 1)
    {
        resultpipe = pipe(p->fd + i * 2);
        if (resultpipe < 0)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    p->fd_index = 0;
    execute_ast(ast, p);
    i = 0;
    while (i < 2 * p->total_cmds)
    {
        close(p->fd[i]);
        i++;
    }
    free(p->fd);
    free_matrix(p->env);
}
