/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils08.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:48:06 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/01 20:02:32 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}

char	*trim_sp(const char *str)
{
	size_t	len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (len > 0 && ft_isspace((unsigned char)str[len - 1]))
		len--;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, str, len);
	result[len] = '\0';
	return (result);
}

/* 
 * Removes, if found, substr from old_str and returns new_str.
 */
char	*remove_substr(char *substr, char *old_str)
{
	int		i;
	int		j;
	int		substr_len;

	if (!substr || !old_str)
		return (old_str);
	substr_len = ft_strlen(substr);
	i = 0;
	while (old_str[i])
	{
		if (ft_strncmp(old_str + i, substr, substr_len) == 0)
			break ;
		i++;
		if (!old_str[i])
			return (old_str);
	}
	j = i;
	i += substr_len;
	while (old_str[i] && old_str[i] == ' ')
		i++;
	while (old_str[i])
		old_str[j++] = old_str[i++];
	old_str[j] = '\0';
	return (old_str);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

	if (!new)
		return ;
	if (lst)
	{
		if (*lst != NULL)
		{
			aux = *lst;
			while (aux->next)
				aux = aux->next;
			aux->next = new;
			return ;
		}
		*lst = new;
		return ;
	}
}

/* 
 * Appends the suffix str to the base str and returns a new str.
 * If base does not exist, suffix will be returned and vice versa.
 */
char	*append_str(char *base, char *suffix)
{
	char	*result;
	size_t	base_len;
	size_t	suffix_len;

	if (!base && !suffix)
		return (NULL);
	if (!base)
		return (ft_strdup(suffix));
	if (!suffix)
		return (ft_strdup(base));
	base_len = ft_strlen(base);
	suffix_len = ft_strlen(suffix);
	result = ft_malloc((base_len + suffix_len + 2) * sizeof(char));
	ft_strcpy(result, base);
	result[base_len] = ' ';
	ft_strcpy(result + base_len + 1, suffix);
	free(base);
	return (result);
}
