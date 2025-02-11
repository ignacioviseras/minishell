/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_flags_and_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:12:58 by drestrep          #+#    #+#             */
/*   Updated: 2025/02/11 19:49:30 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	manage_quoted_str(t_token *token, char *str, int *i)
{
	char	*aux;
	int		j;

	j = 1;
	aux = get_quoted_str(str + *i, str[*i]);
	while (aux[j] == ' ')
		j++;
	if (aux[j] == '-' && ft_strcmp(token->cmd, "export") != 0)
		token->flags = append_str(token->flags, aux);
	else
		token->args = append_str(token->args, aux);
	*i += ft_strlen(aux);
	free(aux);
}

void	manage_unquoted_str(t_token *token, char *str, int *i)
{
	char	*aux;

	if (findchar(str + *i, ' ') >= 0 && ft_strcmp(token->cmd, "export") != 0)
		aux = ft_substr(str + *i, 0, findchar(str + *i, ' '));
	else
		aux = ft_strdup(str + *i);
	if (aux[0] == '-' && ft_strcmp(token->cmd, "export") != 0)
		token->flags = append_str(token->flags, aux);
	/* else if (aux[0] != '-' && ft_strcmp(token->cmd, "export") == 0)
	{
		token->args = get_export_args(aux);
	} */
	else
		token->args = append_str(token->args, aux);
	*i += ft_strlen(aux);
	free(aux);
}

void	find_args(t_token *token, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		i = skip_quoted_string(str, i);
	while (is_alnum(str[i]) || str[i] == '-' || str[i] == '|' || str[i] == '"'
		|| str[i] == '\'')
		i++;
	while (str[i] && str[i] != '|')
	{
		if (str[i] == '"' || str[i] == '\'')
			manage_quoted_str(token, str, &i);
		else
		{
			while (str[i] == ' ')
				i++;
			manage_unquoted_str(token, str, &i);
		}
	}
}

int	find_quotes_in_word(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return(0);
}

int	is_between_single_quotes(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		else if (str[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

char	*remove_double_quotes(char *str)
{
	char	*unquoted_str;
	int		nbr_of_quotes;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	printf("Str: %s\n", str);
	if (findchar(str, '"') < 0 || is_between_single_quotes(str))
		return (ft_strdup(str));
	nbr_of_quotes = count_quotes(str);
	unquoted_str = ft_malloc((ft_strlen(str) - nbr_of_quotes + 1) \
	* sizeof(char));
	while (str[i])
	{
		if (str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				unquoted_str[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			unquoted_str[j++] = str[i++];
	}
	unquoted_str[j] = '\0';
	return (unquoted_str);
}

void	get_cmd_flags_and_args(t_token *token, char *full_cmd)
{
	char	*unquoted_str;
	int	i;

	i = 0;
	token->cmd = NULL;
	if (!token->cmd && find_quotes_in_word(full_cmd))
	{
		token->cmd = get_unquoted_str(full_cmd);
		i += ft_strlen(token->cmd);
	}
	if (!token->cmd)
	{
		while (is_alpha(full_cmd[i]) || full_cmd[i] == '/' || full_cmd[i] == '_'
			|| full_cmd[i] == '$')
			i++;
		token->cmd = ft_substr(full_cmd, 0, i);
	}
	if (ft_strcmp(token->cmd, "echo") == 0)
	{
		unquoted_str = remove_double_quotes(token->full_cmd);
		free(token->full_cmd);
		token->full_cmd = unquoted_str;
	}
	find_args(token, token->full_cmd);
	/* if (ft_strcmp(token->cmd, "echo") == 0)
	{
		unquoted_str = get_unquoted_str(token->args);
		free(token->args);
		token->args = unquoted_str;
	} */
}
