/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:30:02 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 11:33:56 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void	execute_ast(t_ast *node, t_params *p, t_env *env)
{
	t_token *data;

    if (node == NULL)
        return;
    data = (t_token *)(node->data);
    if (data->type == TOKEN_PIPE)
		handle_pipe(node, p, env);
	else
		before_execute(node, p, env);
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


void init_pipes(t_ast *ast, t_params *p, t_env *env)
{
    int i;
    int resultpipe;

    p->fd = malloc(2 * p->total_cmds * sizeof(int));
    if (!p->fd)
        return;
    ft_memset(p->fd, -1, 2 * p->total_cmds * sizeof(int));
    i = 0;
    while (i < p->total_cmds - 1)
    {
        resultpipe = pipe(p->fd + i * 2);
        if (resultpipe < 0)
        {
            perror("pipe");
            while (i-- > 0)
            {
                close(p->fd[i * 2]);
                close(p->fd[i * 2 + 1]);
            }
            free(p->fd);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    p->fd_index = 0;
    execute_ast(ast, p, env);
    i = 0;
    while (i < 2 * p->total_cmds)
    {
        if (p->fd[i] != -1)
            close(p->fd[i]);
        i++;
    }
    free(p->fd);
    free_matrix(p->env);
}

