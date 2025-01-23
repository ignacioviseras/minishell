/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:04:57 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/23 11:53:16 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_nbr_of_flags(char *args, t_token_type type)
{
	int		nbr_of_flags;
	int		i;

	(void)type;
	nbr_of_flags = 0;
	i = 0;
	while (args && args[i])
	{
		i = skip_quoted_string(args, i);
		if (args[i++] == '-')
			nbr_of_flags++;
	}
	return (nbr_of_flags);
}

char	*get_all_flags(char *args, char *token_flags, t_token_type type)
{
	char	**flags;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	flags = ft_malloc((get_nbr_of_flags(args, type) + 1) * sizeof(char *));
	while (args && args[i] && j < get_nbr_of_flags(args, type))
	{
		i = skip_quoted_string(args, i);
		if (args[i] == '-')
			flags[j++] = ft_substr(args + i, 0, copy_len(args + i) + 1);
		i++;
	}
	flags[j] = NULL;
	j = 0;
	while (flags[j])
	{
		temp = token_flags;
		token_flags = ft_strjoin(token_flags, flags[j++]);
		free(temp);
	}
	free_matrix(flags);
	return (token_flags);
}

void	organize_redirection_tokens(t_lexer *lexer, t_token *tokens)
{
	t_token	*aux;
	char	*str;
	char	*temp_str;

	aux = tokens;
	str = NULL;
	while (aux && aux->type > 1)
	{
		temp_str = ft_strjoin(str, aux->flags);
		free(str);
		str = temp_str;
		free(aux->flags);
		aux->flags = NULL;
		aux = aux->next;
	}
	add_token(&lexer->tokens, create_token(TOKEN_STRING, str));
	free(str);
	free(tokens->flags);
	free(tokens->full_cmd);
	tokens->flags = NULL;
	tokens->full_cmd = ft_strjoin(tokens->cmd, tokens->args);
}

void	organize_strings(t_token *tokens, t_token *aux)
{
	char	*temp_str;

	temp_str = ft_strjoin(tokens->args, aux->flags);
	free(tokens->args);
	free(tokens->full_cmd);
	free(aux->full_cmd);
	free(aux->flags);
	tokens->args = temp_str;
	tokens->full_cmd = ft_strjoin(tokens->cmd, tokens->args);
	aux->full_cmd = ft_strjoin(aux->cmd, aux->args);
	aux->flags = NULL;
}

void	organize_tokens(t_lexer *lexer, t_token *tokens)
{
	t_token	*start;

	start = tokens;
	while (tokens)
	{
		/* if (tokens->type == 0)
		{
			
		} */
		if (tokens->type == 0 && tokens->next \
		&& findchar(tokens->args, '-' >= 0))
			tokens->flags = get_all_flags(tokens->args, \
			tokens->flags, tokens->type);
		tokens = tokens->next;
	}
	tokens = start;
	(void)lexer;
	/* while (tokens)
	{
		printf("%s\n", tokens->full_cmd);
		tokens = tokens->next;
	} */
	//printf("SALE\n");
	//exit(0);
}

/* void	organize_tokens(t_lexer *lexer, t_token *tokens)
{
	t_token	*start;
	t_token	*aux;

	start = tokens;
	if (tokens && tokens->type > 1 && tokens->flags)
	{
		organize_redirection_tokens(lexer, tokens);
		tokens = tokens->next;
	}
	while (tokens)
	{
		aux = tokens->next;
		while (tokens->type == TOKEN_STRING && aux && aux->type > 1)
		{
			organize_strings(tokens, aux);
			aux = aux->next;
		}
		if (tokens->type == 0 && tokens->next \
		&& findchar(tokens->args, '-' >= 0))
			tokens->flags = get_all_flags(tokens->args, \
			tokens->flags, tokens->type);
		tokens = tokens->next;
	}
	tokens = start;
} */
