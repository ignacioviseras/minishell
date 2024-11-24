/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:43:00 by igvisera          #+#    #+#             */
/*   Updated: 2024/11/24 22:57:27 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

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
		// init_pipes(ast, p);
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
	int reslt_exec;
	if (p->env && p->env[0])
		get_path(p->env, p, data);
	else if (ft_strchr(data->cmd, '/') && ft_strchr(data->cmd, '/'))
		tramited("", p, data);
	reslt_exec = execve(p->cmd_path, p->cmd_exec, p->env);
	printf("llega??");
	if (reslt_exec < 0)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
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

// void	execute_node(t_ast *node, t_params *p)
// {
// 	int pid;
// 	int i;

// 	i = -1;
//     t_token *data = (t_token *)(node->data);
// 	pid = fork();
// 	if (pid == 0)// pipe hijo
// 	{
// 		if (p->fd_index != 0)//si no es el primer comando
// 			dup_read(p);//duplica el extremo de lectura
// 		if (p->fd_index < 2 * (p->total_cmds - 1))//si no es el último comando
// 			dup_write(p);//duplica el extremo de escritura
// 		while (++i < 2 * p->total_cmds)//cierra todos los extremos de los pipes
// 			close(p->fd[i]);
// 		init_execute(data, p, node);
// 	}
// 	//------------------------------
// 	//creo q no hace falta estos close pq tengo un bucle de close
// 	//------------------------------
// 	else if(pid > 0)//proceso padre
// 	{
// 		close(p->fd[p->fd_index]);//cerrar extremos usados
// 		close(p->fd[p->fd_index + 1]);
// 		waitpid(pid, NULL, 0);//CAMBIAR ESTE WAIT
// 	}
// }

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
        init_execute(data, p);
    }
    else if (pid > 0)
    {
        close(p->fd[p->fd_index]);
        close(p->fd[p->fd_index + 1]);
        waitpid(pid, NULL, 0);
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

// void init_param(t_params *p, int *fd, int fd_index)
// {
// 	p->fd = fd;
// 	p->fd_index = fd_index;
	
// }

void init_pipes(t_ast *ast, t_params *p)
{
    int i;
    int fd[2 * p->total_cmds];

    i = 0;
    while (i < p->total_cmds)
    {
        if (pipe(fd + i * 2) < 0)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    p->fd = fd;
    p->fd_index = 0;
    execute_ast(ast, p);
    i = 0;
    while (i < 2 * p->total_cmds)
    {
        close(fd[i]);
        i++;
    }
    free_matrix(p->env);
}

// void init_pipes(t_ast *ast, t_params *p)
// {
// 	int i;
// 	int resultpipe;
// 	int fd[2 * p->total_cmds];

// 	i = 0;
// 	while (i < p->total_cmds)
// 	{
// 		resultpipe = pipe(fd + i * 2);
// 		if (resultpipe < 0)
// 		{
// 			perror("pipe");
// 			exit(1);
// 		}
// 		init_param(p, fd, 0);
// 		execute_ast(ast, p);
// 		free_matrix(p->env);
// 		i++;
// 	}
// 	while (i > 2 * p->total_cmds)
// 	{
//     	close(fd[i]);
// 		i--;
// 	}
// }


// int	tramited(char *path, t_params *p, t_ast *ast, t_token *t)
// {
// 	char		**dir;

// 	dir = ft_split(path + 5, ':');
// 	p->cmd_path = load_param(dir, t->full_cmd);
// 	p->cmd_exec = split_formated(t->full_cmd, ' ');
// 	free_matrix(dir);
// 	if (p->cmd_path != NULL)
// 		init_pipes(ast, p, p->env);
// 	else
// 	{
// 		free(p->cmd_path);
// 		free_matrix(p->cmd_exec);
// 		exit(1);
// 	}
// 	return (0);
// }

// create_pipes(ast, resultpipe);
// resultpipe = pipe(fd_pipe);
// if (resultpipe == -1)
// {
// 	perror("pipe");
// 	exit(1);
// }
// pid = fork();
// dprintf(2, "Llegas??\n");
// if (pid == 0)
// 	child_pipe(fd_pipe, p->file1, p->comand_path1, p->comand1, env);
// else
// 	father_pipe(fd_pipe, p->file2, p->comand_path2, p->comand2, env);
// wait(&status);	


// esto gestionara los builst
// if (ft_strcmp(data->cmd, "cd") == 0) {
//     *is_builtin = 1;
//     handle_cd(data);
//     return;
// }
// Ejecuta el comando
//------------------------
// execve(path, comand, env);
// perror("execve");
//------------------------
// if (execve(data->args[0], data->args, environ) < 0)
// {
//     perror(data->args[0]);
//     exit(EXIT_FAILURE);
// }
