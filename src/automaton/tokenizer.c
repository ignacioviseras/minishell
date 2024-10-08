/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:19:37 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/08 16:47:56 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Creates a new token with the specified type and value, 
 * allocating memory and duplicating the token's value string.
 */
t_token	*create_token(token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = ft_strdup(value);
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

/*
 * Tokenizes strings based on quotes or delimiters. 
 * If the input starts with a quote (' or "), it extracts the quoted string. 
 * Otherwise, it tokenizes until encountering a space or operator (|, >, <). 
 */
void	tokenize_strings(t_automata *automata, char *input, int *i)
{
	int		start;
	char	quote;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|' \
		&& input[*i] != '>' && input[*i] != '<')
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
		}
		(*i)++;
	}
	strncpy(automata->buf, input + start, *i - start);
	automata->buf[*i - start] = '\0';
	add_token(&automata->tokens, create_token(TOKEN_STRING, automata->buf));
}

/*
 *	The tokenizer is in charge of separating everything into tokens,
 *	differentiating between operators, redirections and strings.
 */
void	tokenizer(t_automata *automata, char *input, int *i)
{
	if (input[*i] == '|')
	{
		add_token(&automata->tokens, create_token(TOKEN_PIPE, "|"));
		(*i)++;
	}
	else if ((input[*i] == '>' && input[*i + 1] != '>') \
		|| (input[*i] == '<' && input[*i + 1] != '<'))
	{
		if (input[(*i)++] == '>')
			add_token(&automata->tokens, create_token(TOKEN_OUTPUT, ">"));
		else
			add_token(&automata->tokens, create_token(TOKEN_INPUT, "<"));
	}
	else if ((input[*i] == '>' && input[*i + 1] == '>') \
		|| (input[*i] == '<' && input[*i + 1] == '<'))
	{
		if (input[*i] == '>')
			add_token(&automata->tokens, create_token(TOKEN_APPEND, ">>"));
		else
			add_token(&automata->tokens, create_token(TOKEN_HEREDOC, "<<"));
		(*i) += 2;
	}
	else
		tokenize_strings(automata, input, i);
}
