/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils04.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:10:36 by drestrep          #+#    #+#             */
/*   Updated: 2024/10/24 14:13:01 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	index;

	index = 0;
	while (s && s[index] != '\0')
	{
		if (s[index] == (unsigned char)c)
			return ((char *)s + index);
		index++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	return (NULL);
}

char	*ft_str_toupper(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

static int	n_words(char const *s, char c)
{
	int	words;
	int	index;

	index = 0;
	words = 0;
	index = 0;
	if (!s)
		return (0);
	while (s[index] && s[index] == c)
		index++;
	while (s[index] != '\0')
	{
		if (s[index] == c)
		{
			while (s[index] && s[index] == c)
				index++;
			words++;
		}
		else
			index++;
	}
	if (s[index - 1] && s[index - 1] != c)
		words++;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len_word;
	char	**str;

	i = 0;
	str = ft_calloc(n_words(s, c) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (s && *s != '\0')
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			return (str[i] = NULL, str);
		if (!ft_strchr(s, c))
			len_word = ft_strlen(s);
		else
			len_word = ft_strchr(s, c) - s;
		str[i] = ft_substr(s, 0, len_word);
		if (!str[i++])
			return (free_matrix(str), NULL);
		s += len_word;
	}
	return (str[i] = NULL, str);
}

char	**split_formated(char const *s, char c)
{
	size_t	i;
	size_t	len_word;
	char	**str;

	i = 0;
	str = ft_calloc(n_words(s, c) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (s && *s != '\0')
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		if (!ft_strchr(s, c))
			len_word = ft_strlen(s);
		else
			len_word = ft_strchr(s, c) - s;
		str[i] = ft_substr(s, 0, len_word);
		if (!str[i++])
			return (free_matrix(str), NULL);
		s += len_word;
	}
	str[i] = NULL;
	return (str);
}
