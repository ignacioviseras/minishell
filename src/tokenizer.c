/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:19:37 by drestrep          #+#    #+#             */
/*   Updated: 2024/09/30 15:39:00 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*create_token(token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->type = type;
	token->value = strdup(value);
	token->next = NULL;
	return (token);
}

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

void	tokenize_words(t_automata *automata, char *input, int *i)
{
	int		start;
	char	quote;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		quote = input[*i];
		start = (*i)++;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		if (input[*i] == quote)
			(*i)++;
		strncpy(automata->buf, input + start, *i - start);
		automata->buf[*i - start] = '\0';
		add_token(&automata->tokens, create_token(TOKEN_STRING, automata->buf));
	}
	else
	{
		start = *i;
		while (input[*i] && input[*i] != ' ' && input[*i] != '|' \
			&& input[*i] != '>' && input[*i] != '<')
			(*i)++;
		strncpy(automata->buf, input + start, *i - start);
		automata->buf[*i - start] = '\0';
		add_token(&automata->tokens, create_token(TOKEN_STRING, automata->buf));
	}
}

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
			add_token(&automata->tokens, create_token(TOKEN_OUT, ">"));
		else
			add_token(&automata->tokens, create_token(TOKEN_IN, "<"));
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
		tokenize_words(automata, input, i);
}
