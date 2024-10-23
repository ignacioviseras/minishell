/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:12:20 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/23 11:39:23 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void	**free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	return (free(str), NULL);
}

void	free_env(t_envi *envi)
{
	t_envi *temp;

	while (envi)
	{
		temp = envi;
		envi = envi->next;
		free(temp->content);
		free(temp);
	}
}

void free_token(t_token *token) {
    while (token) {
        t_token *temp = token;
        token = token->next;
        free(temp->value);
        free(temp);
    }
}
