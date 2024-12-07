/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:33:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/12/07 19:14:40 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Creates a new token with the specified type and value,
 * allocating memory and duplicating the token's value string.
 */
t_token	*create_token(t_token_type type, char *buf)
{
	t_token	*token;
	int		space_pos;

	token = ft_malloc(sizeof(t_token));
	token->full_cmd = ft_strdup(buf);
	token->type = type;
	space_pos = findchar(buf, ' ');
	if (space_pos > 0 && space_pos + 1 != (int)ft_strlen(buf))
		create_args(token, buf, space_pos);
	else
	{
		token->cmd = ft_strdup(buf);
		token->args = NULL;
		token->flags = NULL;
	}
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
