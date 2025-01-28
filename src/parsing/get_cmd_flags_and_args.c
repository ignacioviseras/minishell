/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_flags_and_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:12:58 by drestrep          #+#    #+#             */
/*   Updated: 2025/01/28 19:58:26 by drestrep         ###   ########.fr       */
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

	if (findchar(str + *i, ' ') >= 0)
		aux = ft_substr(str + *i, 0, findchar(str + *i, ' '));
	else
		aux = ft_strdup(str + *i);
	if (aux[0] == '-' && ft_strcmp(token->cmd, "export") != 0)
		token->flags = append_str(token->flags, aux);
	else
		token->args = append_str(token->args, aux);
	*i += ft_strlen(aux);
	free(aux);
}

void	find_args(t_token *token, char *str)
{
	int		i;

	i = 0;
	if (str[i] == '"' || str[i] == '\'')
		i = skip_quoted_string(str, i);
	while (is_alnum(str[i]) || str[i] == '-' || str[i] == '|' || \
			str[i] == '"' || str[i] == '\'')
		i++;
	while (str[i] && str[i] != '|')
	{
		if (str[i] == '"' || str[i] == '\'')
			manage_quoted_str(token, str, &i);
		else if (is_alnum(str[i]) || str[i] == '-')
			manage_unquoted_str(token, str, &i);
		else
			i++;
	}
}

void	get_cmd_flags_and_args(t_token *token, char *full_cmd)
{
	int	i;

	i = 0;
	token->cmd = NULL;
	if (!token->cmd && (full_cmd[i] == '\'' || full_cmd[i] == '"'))
	{
		token->cmd = get_unquoted_str(full_cmd);
		i += ft_strlen(token->cmd);
	}
	if (!token->cmd)
	{
		while (is_alpha(full_cmd[i]) || full_cmd[i] == '/' || \
		full_cmd[i] == '_' || full_cmd[i] == '$')
			i++;
		token->cmd = ft_substr(full_cmd, 0, i);
	}
	find_args(token, full_cmd);
}
