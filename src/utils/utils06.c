/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils06.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:20:14 by igvisera          #+#    #+#             */
/*   Updated: 2024/11/23 21:07:21 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int	ft_isalnum(char	c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int is_alpha(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int is_number(char c)
{
    return (c >= '0' && c <= '9');
}

int is_alnum(char c)
{
    return (is_alpha(c) || is_number(c));
}

int is_valid(char *str)
{
    int i;

	i = 1;
	if (!str || (!is_alpha(str[0]) && str[0] != '_'))
        return (1);
    while (str[i] != '\0')
	{
        if (!is_alnum(str[i]) && str[i] != '_')
            return (1);
        i++;
    }
    return (0);
}

char	*ft_strjoin_cmd(char *s1, char *s2)
{
	char	*c1;
	size_t	len_max;

	len_max = (ft_strlen(s1) + ft_strlen(s2)) + 2;
	if (!s1 || !s2)
		return (NULL);
	c1 = (char *)ft_calloc(len_max, sizeof(char));
	if (!c1)
		return (NULL);
	ft_newstrlcpy(c1, (char *)s1, ft_strlen((const char *)s1) + 1);
	ft_strlcat(c1, s2, len_max);
	return (c1);
}