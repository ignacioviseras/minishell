/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_add_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:33:27 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/18 18:55:42 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	number_of_spaces(char *str, int i)
{
	int	spaces;

	spaces = 0;
	while (str[i++] == ' ')
		spaces++;
	return (spaces);
}

/*
 * Creates a new token with the specified type and value,
 * allocating memory and duplicating the token's value string.
 */
t_token	*create_token(t_token_type type, char *buf)
{
	t_token	*token;
	int		space_pos;

	token = ft_malloc(sizeof(t_token));
	ft_bzero(token, sizeof(t_token));
	token->full_cmd = ft_strdup(buf);
	token->type = type;
	space_pos = findchar(buf, ' ');
	if (((space_pos > 0 && space_pos + number_of_spaces(token->full_cmd, \
		space_pos) != (int)ft_strlen(buf)) || (findchar(token->full_cmd, \
		'>') > -1 || findchar(token->full_cmd, '<') > -1)) && token->type == 0)
	{
		get_redirections(token);
		get_cmd_flags_and_args(token, token->full_cmd);
	}
	else
		token->cmd = get_unquoted_str(buf);
	token->next = NULL;
	return (token);
}

/*
 * Adds a new token to the end of the token list.
 * If the list is empty, the new token becomes the head.
 */
void	add_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (*head == NULL)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

char	*update_args(char *args)
{
	if (ft_strcmp(args, "") == 0)
	{
		free(args);
		args = NULL;
	}
	return (args);
}
