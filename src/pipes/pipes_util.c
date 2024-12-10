/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:43:00 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/10 16:06:17 by drestrep         ###   ########.fr       */
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

void redirect_output(t_token *data, t_ast *ast, t_params *p)
{
    if (ft_strcmp(data->cmd, ">") != 0)
    {
        int original_stdout;
        // printf("accedes?????????\n");
        int fd = open(data->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // original_stdin = dup(STDOUT_FILENO);
        original_stdout = dup(STDOUT_FILENO);
        if (fd < 0) {
            perror("open output");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2 output");
            exit(EXIT_FAILURE);
        }
        close(fd);
        execute_node(ast->left, p);
        if (dup2(original_stdout, STDOUT_FILENO) < 0)
        {
            perror("restore stdin");
            exit(EXIT_FAILURE);
        }
        close(original_stdout);
    }
}

void init_redirct_out(t_ast *ast, t_params *p)
{
    if (ast->right->data != NULL)
    {
        t_token *token;

        token = (t_token *)(ast->right->data);
        printf("nombre arc '%s'\n", token->cmd);
        redirect_output(token, ast, p);

    }
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

//----------- GET-ENV ----------------
char *trim_quotes(char *str) {
    size_t len;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        str[len - 1] = '\0';
        return str + 1;
    }
    return str;
}

char *get_env_value(const char *key, char **environ)
{
    size_t key_len;
    char **env;

    if (!key || !environ)
        return "";
    key_len = ft_strlen(key);
    env = environ;
    while (*env)
    {
        if (ft_strncmp(*env, key, key_len) == 0 && (*env)[key_len] == '=')
            return trim_quotes(*env + key_len + 1);
        env++;
    }
    return "";
}

char *replace_env_vars(const char *input, char **environ)
{
    size_t len;
    size_t rsult_size;
    char *result;
    size_t i;
    size_t j;

    if (!input || !environ)
        return (NULL);
    len = ft_strlen(input);
    rsult_size = len * 2;
    result = malloc(rsult_size + 1);
    if (!result)
        return NULL;
    i = 0;
    j = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '$' && (i == 0 || input[i - 1] != '\\'))
        {
            i++;
            size_t start = i;
            while (input[i] != '\0' && (isalnum(input[i]) || input[i] == '_'))
                i++;
            if (i > start)
            {
                char var_name[128];
                ft_strncpy(var_name, input + start, i - start);
                var_name[i - start] = '\0';
                const char *value = get_env_value(var_name, environ);
                size_t value_len = ft_strlen(value);

                // Redimensionar result si es necesario
                if (j + value_len >= rsult_size) {
                    rsult_size = (j + value_len) * 2; // Duplicar el tamaño actual
                    char *new_result = realloc(result, rsult_size + 1);
                    if (!new_result) {
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                }

                ft_strcpy(result + j, value);
                j += value_len;
            }
        }
        else
        {
            if (j >= rsult_size) {
                rsult_size *= 2; // Duplicar el tamaño si se necesita más espacio
                char *new_result = realloc(result, rsult_size + 1);
                if (!new_result) {
                    free(result);
                    return NULL;
                }
                result = new_result;
            }
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';
    return result;
}

//----------------------------------

void write_heredoc(int fd_file, char *delimiter, char **env)
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
            //if $
            if (ft_strchr(buffer, '/') == 0)
                content = write(fd_file, replace_env_vars(buffer, env), ft_strlen(buffer));
            else
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

void handle_heredoc(t_token *data, t_ast *node, t_params *p)
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
        write_heredoc(fd_file, data->cmd, p->env);

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
    {
        init_redirct_out(node, p);
        // init_redirct_out(node);
    }
    else if (ft_strcmp(data->cmd, ">>") == 0)
        redirect_append(data);
    else if (ft_strcmp(data->cmd, "<<") == 0)
    {
        handle_heredoc(data, node, p);
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
