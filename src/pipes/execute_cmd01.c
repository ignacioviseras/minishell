/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:32:52 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/28 22:03:27 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int	tramited(char *path, t_params *p, t_token *t)
{
	char		**dir;

	dir = ft_split(path, ':');
	p->cmd_path = load_param(dir, t->cmd);
	p->cmd_exec = split_formated(t->full_cmd, ' ');
	free_matrix(dir);
	if (p->cmd_path != NULL)
        execute_cmd(p);
	else
	{
		free(p->cmd_path);
		free_matrix(p->cmd_exec);
		exit(127);//TODO aqui se tendria q liberar todos los datos
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
        handle_redirection(node, p, env, have_redirect);//ejecucion de las redirecciones
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
                handle_pipe(node, p, env);  // mueve la pipe es para casos dnd las redirect estan por el centro
            else if (data && builtin == 0)
            {
                build_switch(env, node, data);
                exit(0);
            }
            else
                init_execute(data, p);//ejecucion normal
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
