/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:47:37 by igvisera          #+#    #+#             */
/*   Updated: 2024/10/30 14:31:22 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

// void command_echo(t_token *tokens)
// {
// 	int x;

// 	if (ft_charcmp(tokens->next->value[0], '-') == 0)
// 	{
// 		x = flags_validator(tokens->next->value, "n e E");
// 		//tendria q meter algo por si es la n
// 		if (x == 0)
// 			printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
// 		else
// 			//Aqui tendria q pintar todo 
// 			/*
// 				echo -neEa hola
// 				->	-neEa hola
			
// 			*/
// 	}
// }

char *get_value(t_env **envi, char *find)
{
    t_env *current = *envi;
    
    while (current)
    {
        if (ft_strcmp(find, current->key) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

char	*get_var(char *str)
{
	char *variable;
	int len_variable;
	int len_all;

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
        return NULL;
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

void	command_export(t_token *tokens, t_env *env)
{
	char **splt_vars;
	int x;

	if (tokens->args == NULL)
		print_env(env, 1);
	else
	{
		if (tokens->flags)
		{
			if (ft_charcmp(tokens->flags[0], '-') == 0)
			{
				if (flags_validator(tokens->flags, "f n p") == 0)
				{
					printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
					return;
				}
			}
		}
		else
		{
			splt_vars = ft_split(tokens->args, ' ');
			if (!splt_vars)
				return;//TODO mirar esto dara errores el control del malloc
			x = -1;
			while (splt_vars[++x])
			{
				if (!ft_strchr(splt_vars[x], '='))
					add_bottom(&env, new_node(splt_vars[x], NULL, 1));
				else
					add_bottom(&env, new_node(get_var(splt_vars[x]), get_content_var(splt_vars[x]), 1));
			}
			free(splt_vars);
		}
	}
}


void	print_env(t_env *env, int flag)
{
	// aqui tengo q modigicar algo para q cuando ejecute el export pinte declare -x para las var que solo tienen key
	// y no pinte en la opcion de env las q no tienen contenido
	int	i;

	i = 1;
	if (!env)
		printf("Sin contenido\n");
	while (env)
	{
		if (flag == 1)
		{
			printf("declare -x ");
			if (env->value != NULL)
				printf("%s=\"%s\"\n", env->key, env->value);
			else
				printf("%s\n", env->key);
		}
		else if(env->hide == 0)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
		i++;
	}
}


void	command_unset(t_token *tokens, t_env *env)
{
	char **splt_vars;
	int x;

	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
		{
			x = flags_validator(tokens->flags, "f v n");
			if (x == 0)
				printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
			else
			{
				printf("bash: unset: -%c: invalid option\nunset: usage: unset [-f] [-v] [-n] [name ...]\n", \
				tokens->flags[x]);
			}
		}
	}
	else
	{
		splt_vars = ft_split(tokens->args, ' ');
		if (!splt_vars)
			return;//TODO mirar esto dara errores el control del malloc
		x = -1;
		while (splt_vars[++x])
		{
			if (!ft_strchr(splt_vars[x], '='))
				remove_node(&env, splt_vars[x]);
			else
				printf("bash: unset: `%s': not a valid identifier\n", splt_vars[x]);
		}
		free(splt_vars);
	}
}

void command_clear(t_token *tokens)
{
	int x;

	x = 2;
	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
		{
			x = flags_validator(tokens->flags, "T V x");
			if (x == 0)
				printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
			else
				printf("clear: invalid option -- '%c'\n", tokens->flags[x]);
		}
	}
	else if (tokens->args == NULL)
		printf("\033[2J\033[H");
	if (tokens->args != NULL || x == 1)
	{
		printf("Usage: clear [options]\n\nOptions:\n");
		printf("  -T TERM     use this instead of $TERM\n");
		printf("  -V          print curses-version\n");
		printf("  -x          do not try to clear scrollback\n");
	}
}

void print_echo(char *input)
{
	// int no_newline;
	// int i;
	
	// no_newline = 0;
    // i = 0;
    // while (input[i] == '-')
	// {
    //     int j = i + 1;
    //     if (input[j] == 'n')
	// 	{
    //         no_newline = 1;
    //         while (input[j] == 'n')
    //             j++;
    //         i = j;
    //         while (input[i] == ' ')
    //             i++;
    //     }
	// 	else
    //         break;
    // }
    // printf("%s", &input[i]);
    // if (!no_newline)
    //     printf("\n");
	int no_newline = 1; // Comenzamos con la suposición de que no se imprimirá un salto de línea
    int i = 0;

    // Verifica si hay prefijos de -n
    while (input[i] == '-') {
        int j = i + 1;

        // Comprobar si el siguiente carácter es 'n'
        if (input[j] == 'n') {
            while (input[j] == 'n') {
                j++; // Continuamos mientras sean 'n'
            }
            // Avanzamos i al siguiente argumento
            i = j;
            while (input[i] == ' ') {
                i++; // Omitir espacios
            }
        } else {
            // Si encontramos un prefijo que no es 'n', dejamos de contar
            break;
        }
    }

    // Imprimimos el resto de la cadena
    printf("%s", &input[i]);
    if (no_newline) {
        printf("\n"); // Solo imprimimos el salto de línea si no se encontró un argumento que comience con '-n'
    }
}

void command_echo(t_token *tokens)
{
	int x;
	
	if (tokens->flags)
	{
		if (ft_charcmp(tokens->flags[0], '-') == 0)
		{
			x = flags_validator(tokens->flags, "e E");
			if (x == 0)
				printf("NO ESTAN INPLEMENTADAS LAS FLAGS\n");
			else
			{
				print_echo(tokens->args);
				printf("1. '%s'\n", tokens->args);
			}
		}
	}
	else
		printf("%s\n", tokens->args);
}
