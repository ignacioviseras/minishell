/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:08 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/04 16:16:45 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_var(char *str)
{
	char	*variable;
	int		len_variable;
	int		len_all;

	len_all = 0;
	len_variable = 0;
	len_all = ft_strlen(str);
	len_variable = ft_strlen(ft_strchr(str, '='));
	variable = ft_substr(str, 0, len_all - len_variable);
	return (variable);
}

char	*get_content_var(char *str)
{
	char	*finder;
	char	*variable;
	int		start;
	int		end;

	finder = ft_strchr(str, '=');
	if (!finder || *(finder + 1) == '\0')
		return (NULL);
	finder++;
	start = 0;
	while (finder[start] == '"' || finder[start] == '\'')
		start++;
	end = ft_strlen(finder) - 1;
	while (end > start && (finder[end] == '"' || finder[end] == '\''))
		end--;
	if (start > end)
		return (ft_strdup(""));
	variable = ft_substr(finder, start, end - start + 1);
	return (variable);
}

int	validate_export(char *key, char *value)
{
	if (is_valid(key) == 1)
	{
		if (value == NULL)
		{
			printf("bash: export: `%s':", key);
			printf(" not a valid identifier\n");
		}
		else
		{
			printf("bash: export: `%s=%s':", key, value);
			printf(" not a valid identifier\n");
		}
		g_exit_status = 2;
		return (1);
	}
	return (0);
}
