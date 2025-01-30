/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:35:08 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/30 15:00:34 by igvisera         ###   ########.fr       */
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
