/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:53:37 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/15 13:23:16 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = c;
		i++;
	}
	return (b);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*k;

	i = 0;
	k = (char *) s;
	while (i < n)
		k[i++] = 0;
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;	
	size_t	j;
	char	*s2;

	i = 0;
	j = 0;
	while (s1[j])
		j++;
	s2 = (char *)malloc((j + 1) * sizeof (const char));
	if (s2 == NULL)
		return (NULL);
	while (i < j)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/* 
t_ast	*parsing(t_token **tokens)
{
	t_token	*current_node;
	t_ast	*root;

	current_node = *tokens;
	if (current_node && current_node->type == TOKEN_STRING)
	{
		root = create_ast_node(TOKEN_STRING, current_node = current_node->next->value);
		current_node = current_node->next;
	}
	if (current_node && current_node->type == TOKEN_PIPE)
	{
		root->left = parsing(tokens);  // Parse the command on the left of the pipe
		root = create_ast_node(TOKEN_PIPE, current_node = current_node->next->value);
		*tokens = (*tokens)->next->next;
		current_node = current_node->next;
		root->right = parsing(current_node); // Parse the command on the right of the pipe
	}
	if (current_node && current_node->type == TOKEN_OUTPUT)
	{
		root->left = parsing(tokens);
		root = create_ast_node(TOKEN_OUTPUT, current_node = current_node->next->value);
		*tokens = (*tokens)->next->next;
		current_node = current_node->next;
		root->right = parsing(current_node);
	}
	if (current_node && current_node->type == TOKEN_APPEND)
	{
		root->left = parsing(tokens);
		root = create_ast_node(TOKEN_APPEND, current_node = current_node->next->value);
		*tokens = (*tokens)->next->next;		
		current_node = current_node->next;
		root->right = parsing(current_node);
	}
	if (current_node && current_node->type == TOKEN_INPUT)
	{
		root->left = parsing(tokens);
		root = create_ast_node(TOKEN_INPUT, current_node = current_node->next->value);
		*tokens = (*tokens)->next->next;
		current_node = current_node->next;
		root->right = parsing(current_node);
	}
	if (current_node && current_node->type == TOKEN_HEREDOC)
	{
		root->left = parsing(tokens);
		root = create_ast_node(TOKEN_HEREDOC, current_node = current_node->next->value);
		*tokens = (*tokens)->next->next;
		current_node = current_node->next;
		root->right = parsing(current_node);
	}
	return (root);
} */