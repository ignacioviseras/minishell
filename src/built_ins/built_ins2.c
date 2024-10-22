/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:37 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/22 12:05:57 by igvisera         ###   ########.fr       */
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

char *env_finder(t_envi **envi, char *find)
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
}

void	print_envi(t_envi *envi)
{
	int	i;

	i = 1;
	if (!envi)
		printf("Sin contenido\n");
	while (envi != NULL)
	{
		printf("%d. cotent='%s\n", i, envi->content);
		envi = envi->next;
		i++;
	}
}

void init_env(char **env, t_envi **envi)
{
    int	x;

	x = 0;
    while (env[x])
    {
        add_bottom(envi, create_node(env[x]));
        x++;
    }

}
