/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:32:52 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 11:32:49 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int	have_path(char **env)
{
	int	x;

	x = 0;
	while (env[x])
	{
		if (ft_strncmp("PATH=", env[x], 5) == 0)
			return (1);
		x++;
	}
	return (0);
}

void init_execute(t_token *data, t_params *p)
{
	if (have_path(p->env) == 1)
		get_path(p->env, p, data);
	else if (ft_strchr(data->cmd, '/'))
		tramited("", p, data);
    else
		tramited("", p, data);
	return;
}
int have_redirection(t_token *token)
{
    t_redirect_file	*redirection;

    if (token->outfiles)
    {
        redirection = (t_redirect_file *)token->outfiles->content;
        if (redirection)
            return (redirection->type);
    }    
    else if (token->infiles)
    {
        redirection = (t_redirect_file *)token->infiles->content;
        if (redirection)
            return (redirection->type);
    }
    return (-1);
}

void before_execute(t_ast *node, t_params *p, t_env *env)
{
    t_token *data;
    int     have_redirect;

    data = (t_token *)(node->data);
    have_redirect = have_redirection(data);
    if (have_redirect != -1)
        handle_redirection(node, p, env, have_redirect);
    else
        execute_node(node, p, env);
}

void execute_node(t_ast *node, t_params *p, t_env *env)
{
    t_token *data;
    int     status;
    int     builtin;
    int     pid;
    int     i;


    data = (t_token *)(node->data);
    builtin = is_builtin(data->cmd);
    if (p->total_cmds == 1 && builtin == 0)
        build_switch(env, node, data);
    else
    {
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
            if (data && data->type == TOKEN_PIPE)
                handle_pipe(node, p, env);
            else if (data && builtin == 0)
            {
                build_switch(env, node, data);
                exit(0);
            }
            else
                init_execute(data, p);
        }
        else if (pid > 0)
        {
            close(p->fd[p->fd_index + 1]);
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                g_exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                g_exit_status = 128 + WTERMSIG(status);
        }
        else
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }
}


// void execute_child_process(t_ast *node, t_params *p, t_env *env, t_token *data, int builtin)
// {
//     int i;

//     if (p->fd_index != 0)
//         dup_read(p);
//     if (p->fd_index < 2 * (p->total_cmds - 1))
//         dup_write(p);
//     i = 0;
//     while (i < 2 * p->total_cmds)
//     {
//         close(p->fd[i]);
//         i++;
//     }
//     if (data && data->type == TOKEN_PIPE)
//         handle_pipe(node, p, env);
//     else if (data && builtin == 0)
//     {
//         build_switch(env, node, data);
//         exit(0);
//     }
//     else
//         init_execute(data, p);
// }

// void parent_process(t_params *p, int pid)
// {
//     int status;

//     close(p->fd[p->fd_index + 1]);
//     waitpid(pid, &status, 0);

//     if (WIFEXITED(status))
//         g_exit_status = WEXITSTATUS(status);
//     else if (WIFSIGNALED(status))
//         g_exit_status = 128 + WTERMSIG(status);
// }

// void execute_node(t_ast *node, t_params *p, t_env *env)
// {
//     t_token *data;
//     int builtin;
//     int pid;

//     data = (t_token *)(node->data);
//     builtin = is_builtin(data->cmd);

//     if (p->total_cmds == 1 && builtin == 0)
//         build_switch(env, node, data);
//     else
//     {
//         pid = fork();
//         if (pid == 0)
//             execute_child_process(node, p, env, data, builtin);
//         else if (pid > 0)
//             parent_process(p, pid);
//         else
//         {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }
//     }
// }
