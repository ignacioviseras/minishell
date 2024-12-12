/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:32:52 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/12 21:14:43 by igvisera         ###   ########.fr       */
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

    dprintf(2, "dup_read? fd'%d'\n", p->fd[p->fd_index - 2]);
	result = dup2(p->fd[p->fd_index - 2], 0);
    dprintf(2, "****que da result??****'%d'\n", result);
	if(result < 0)
	{
		perror("dup2 input");
		exit(EXIT_FAILURE);
	}
}

void dup_write(t_params *p)
{
	int result;

    dprintf(2, "dup_write? fd'%d'\n", p->fd[p->fd_index + 1]);
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

void execute_node(t_ast *node, t_params *p, t_env *env)
{
    t_token *data;
    int     status;
    int     pid;
    int     i;

    data = (t_token *)(node->data);
    pid = fork();
    if (pid == 0)
    {
        dprintf(2, "LLLLEEEEGAS\n");
        dprintf(2, "cmd q llegas '%s'\n", data->cmd);
        if (p->fd_index != 0)
        {
            dprintf(2, "accedes read? fd'%d'\n", p->fd_index);
            dup_read(p);
        }
        if (p->fd_index < 2 * (p->total_cmds - 1))
        {
            dprintf(2, "accedes write? fd'%d'\n", p->fd_index);
            dprintf(2, "--------tlt cmd-------- '%d'\n", p->total_cmds - 1);
            dup_write(p);
        }
        i = 0;
        while (i < 2 * p->total_cmds)
        {
            close(p->fd[i]);
            i++;
        }
        if (data && ft_strcmp(data->cmd, "|") == 0)
        {
            dprintf(2, "Pipe '%s'\n", data->cmd);
            handle_pipe(node, p, env);  // mueve la pipe es para casos dnd las redirect estan por el centro
        }
        else if (data && (ft_strcmp(data->cmd, "<<") == 0 || ft_strcmp(data->cmd, "<") == 0 || 
                           ft_strcmp(data->cmd, ">") == 0 || ft_strcmp(data->cmd, ">>") == 0))
        {
            dprintf(2, "redirect\n");
            handle_redirection(node, p, env);//ejecucion de las redirecciones
        }
        else if (data && (is_builtin(data->cmd) == 0))
        {
            dprintf(2, "que das?? '%d'\n", is_builtin(data->cmd));
            dprintf(2, "cmd q llegas_built? '%s'\n", data->cmd);
        	build_switch(env, node, data);
            // exit(0);
        }
        else
        {
            // t_token *token;

            // token = (t_token *)(node->right->data);
            // dprintf(2, "node left '%s'\n", token->cmd);
            // if (node->right != NULL)
            // {
            //     dprintf(2, "llegas aqui perr=");
            //     init_redirct_out(node, p, env);
            // }
            init_execute(data, p);//ejecucion normal
        }

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
