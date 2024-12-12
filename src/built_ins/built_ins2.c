/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:37 by igvisera          #+#    #+#             */
/*   Updated: 2024/12/12 16:50:27 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int flags_validator(char *flags, char *command_flags)
{
	int i;
	int j;
	int valid_flag;
	char **cmd_flags_splited;

	if (ft_strcmp(flags, "--help") == 0)
		return (0);
	i = 0;
	cmd_flags_splited = ft_split(command_flags, ' ');
	while (flags[++i] != '\0')
	{
		j = -1;
		valid_flag = 0;
		while (cmd_flags_splited[++j])
		{
			if (ft_charcmp(flags[i], cmd_flags_splited[j][0]) == 0)
			{
				valid_flag = 1;
				break;
			}
		}
		if (!valid_flag)
			return (free_matrix(cmd_flags_splited), i);
	}
	return (free_matrix(cmd_flags_splited), 0);
}

char		*get_home(char *pwd)
{
	int x;
	int slash;
	char *home;

	x = 0;
	slash = 0;
	while (pwd[x] != '\0')
	{
		if (slash == 3)
			break;
		if (pwd[x] == '/')
			slash++;
		x++;
	}
	if (slash == 3)
		x = x-1;	
	home = ft_substr(pwd, 0, x);
	return (home);
}

void command_pwd(t_token *tokens)
{
	int x;

	if (tokens->args == NULL)
	{
		char cwd[4096];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s\n", cwd);
		return;
	}
	if (ft_charcmp(tokens->flags[0], '-') == 0)
	{
		x = flags_validator(tokens->flags, "L P");
		if (x == 0)
			printf("flags are not implemented\n");
		else
			printf("bash: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n", \
				tokens->flags[x]);
	}
}


// aqui tengo q modigicar algo para q cuando ejecute el export pinte 
// declare -x para las var que solo tienen key
// y no pinte en la opcion de env las q no tienen contenido
void	print_env(t_env *env, int flag)
{
	int	i;

	i = 1;
	if (!env)
		printf("Empty\n");
	while (env)
	{
		if (flag == 1)
		{
			if (env->value != NULL)
				printf("%s=\"%s\"\n", env->key, env->value);
			else
				printf("%s\n", env->key);
		}
		else if(env->hide == 0)
		{
            if(env->value != NULL && ft_strcmp(env->value, "\0") != 0)
                printf("%s=%s\n", env->key, env->value);
            else if (ft_strcmp(env->value, "\0") != 0)
                printf("%s\n", env->key);
        }
		env = env->next;
		i++;
	}
}
