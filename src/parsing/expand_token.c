/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:54:03 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/17 18:16:16 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_dollar_sign(t_kv kv, const char *str, char *new_str, \
							t_counters *counters)
{
	if (!is_alnum(str[counters->i + 1]) && str[counters->i + 1] != '_' \
		&& str[counters->i + 1] != '?' && str[counters->i + 1] != '"' \
		&& str[counters->i + 1] != '\'')
	{
		new_str[counters->k++] = str[counters->i++];
		counters->j++;
	}
	else
	{
		ft_strcpy(new_str + counters->k, kv.values[counters->j++]);
		counters->k += ft_strlen(kv.values[counters->j - 1]);
		if (str[counters->i + 2] && !is_alnum(str[counters->i + 2]) \
			&& str[counters->i + 2] != '?' && str[counters->i + 2] != ' ' \
			&& str[counters->i + 2] != '$' && str[counters->i + 2] != '"' \
			&& str[counters->i + 2] != '\'' && str[counters->i + 2] != '-')
			counters->i += ft_strlen(kv.keys[counters->j - 1]);
		else
			counters->i += ft_strlen(kv.keys[counters->j - 1]) + 1;
		if (ft_strcmp(kv.values[counters->j - 1], ""))
			free(kv.values[counters->j - 1]);
	}
}

// char *ft_strndup(const char *s, size_t n) {
//     char *result = (char *)ft_malloc(n + 1);
//     if (!result) return NULL;
//     ft_strncpy(result, s, n);
//     result[n] = '\0';
//     return result;
// }

// void handle_dollar_sign(t_kv kv, const char *str, char *new_str, t_counters *counters) {
//     int var_len = 0;

//     // Avanzar el índice para saltar el signo '$'
//     counters->i++;

//     // Calcular la longitud del nombre de la variable
//     while (is_alnum(str[counters->i + var_len]) || str[counters->i + var_len] == '_') {
//         var_len++;
//     }

//     // Si la longitud es cero, significa que no hay un nombre de variable válido
//     if (var_len == 0) {
//         new_str[counters->k++] = '$';
//         return;
//     }

//     // Extraer el nombre de la variable
//     char *var_name = ft_strndup(&str[counters->i], var_len);

//     // Buscar el valor de la variable en kv.keys
//     char *var_value = NULL;
//     for (int j = 0; kv.keys[j] != NULL; j++) {
//         if (ft_strcmp(kv.keys[j], var_name) == 0) {
//             var_value = kv.values[j];
//             break;
//         }
//     }

//     // Si se encuentra el valor, copiarlo a new_str
//     if (var_value) {
//         ft_strcpy(&new_str[counters->k], var_value);
//         counters->k += ft_strlen(var_value);
//     }

//     // Liberar la memoria del nombre de la variable
//     free(var_name);

//     // Avanzar el índice principal
//     counters->i += var_len;
// }



void	handle_double_quote(t_kv kv, const char *old_str, char *new_str, \
							t_counters *counters)
{
	counters->i++;
	while (old_str[counters->i] && old_str[counters->i] != '"')
	{
		if (old_str[counters->i] == '$')
			handle_dollar_sign(kv, old_str, new_str, counters);
		else
			new_str[counters->k++] = old_str[counters->i++];
	}
	if (old_str[counters->i] == '"')
		counters->i++;
}

void	handle_single_quote(const char *str, char *new_str, \
							t_counters *counters)
{
	counters->i++;
	while (str[counters->i] != '\'' && str[counters->i])
		new_str[counters->k++] = str[counters->i++];
	counters->i++;
}

void	process_string(t_kv kv, char *full_cmd, char *new_str)
{
	t_counters	counters;

	counters.i = 0;
	counters.j = 0;
	counters.k = 0;
	while (full_cmd[counters.i])
	{
		if (full_cmd[counters.i] == '\'')
			handle_single_quote(full_cmd, new_str, &counters);
		else if (full_cmd[counters.i] == '"')
			handle_double_quote(kv, full_cmd, new_str, &counters);
		else if (full_cmd[counters.i] == '$')
			handle_dollar_sign(kv, full_cmd, new_str, &counters);
		else
			new_str[counters.k++] = full_cmd[counters.i++];
	}
	new_str[counters.k] = '\0';
}

char	*expand_token(t_token *token, t_kv kv, int size)
{
	char	*new_str;

	new_str = ft_malloc((size + 1) * sizeof(char));
	process_string(kv, token->full_cmd, new_str);
	free(token->full_cmd);
	return (new_str);
}
