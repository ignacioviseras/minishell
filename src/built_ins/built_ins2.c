/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:37 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/24 02:04:38 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

// void command_echo(t_token *tokens)
// {
// 	int x;

// 	if (ft_charcmp(tokens->next->value[0], '-') == 0)
// 	{
// 		x = flags_validator(tokens->next->value, "n e E");
// 		//tendria q meter algo por si es la n
// 		if (x == 0)
// 			printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
// 		else
// 			//Aqui tendria q pintar todo 
// 			/*
// 				echo -neEa hola
// 				->	-neEa hola
			
// 			*/
// 	}
// }

/* char *env_finder(t_env **envi, char *find)
{
	char *env_path;
	char *found;
	env_path = ft_strjoin(ft_str_toupper(find), "=");
	while ((*envi)->next)
	{
		if (ft_strncmp(find, (*envi)->content, ft_strlen(find)) == 0)
		{
			found = (*envi)->content + ft_strlen(env_path) - 1;
			free(env_path); 
			return(found);
		}
		*envi = (*envi)->next;
	}
	return (free(env_path), NULL);
} */

void	print_env(t_env *env)
{
	int	i;

	i = 1;
	if (!env)
		printf("Sin contenido\n");
	while (env)
	{
		printf("%d. %s=%s\n", i, env->key, env->value);
		env = env->next;
		i++;
	}
}
