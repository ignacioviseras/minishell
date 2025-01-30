/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:43:00 by igvisera          #+#    #+#             */
/*   Updated: 2025/01/30 18:52:49 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int open_heredoc()
{
    int fd_file = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_file < 0)
    {
        perror("open heredoc");
        exit(EXIT_FAILURE);
    }
    return fd_file;
}

//----------- GET-ENV ----------------
// char *trim_quotes(char *str)
// {
//     size_t len;

//     if (!str)
//         return (NULL);
//     len = ft_strlen(str);
//     if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
//         str[len - 1] = '\0';
//         return str + 1;
//     }
//     return str;
// }

// char *get_env_value(const char *key, char **environ)
// {
//     size_t key_len;
//     char **env;

//     if (!key || !environ)
//         return "";
//     key_len = ft_strlen(key);
//     env = environ;
//     while (*env)
//     {
//         if (ft_strncmp(*env, key, key_len) == 0 && (*env)[key_len] == '=')
//             return trim_quotes(*env + key_len + 1);
//         env++;
//     }
//     return "";
// }

// char *replace_env_vars(const char *input, char **environ)
// {
//     size_t len;
//     size_t rsult_size;
//     char *result;
//     size_t i;
//     size_t j;

//     if (!input || !environ)
//         return (NULL);
//     len = ft_strlen(input);
//     rsult_size = len * 2;
//     result = malloc(rsult_size + 1);
//     if (!result)
//         return NULL;
//     i = 0;
//     j = 0;
//     while (input[i] != '\0')
//     {
//         if (input[i] == '$' && (i == 0 || input[i - 1] != '\\'))
//         {
//             i++;
//             size_t start = i;
//             while (input[i] != '\0' && (isalnum(input[i]) || input[i] == '_'))
//                 i++;
//             if (i > start)
//             {
//                 char var_name[128];
//                 ft_strncpy(var_name, input + start, i - start);
//                 var_name[i - start] = '\0';
//                 const char *value = get_env_value(var_name, environ);
//                 size_t value_len = ft_strlen(value);

//                 // Redimensionar result si es necesario
//                 if (j + value_len >= rsult_size) {
//                     rsult_size = (j + value_len) * 2; // Duplicar el tamaño actual
//                     char *new_result = realloc(result, rsult_size + 1);
//                     if (!new_result) {
//                         free(result);
//                         return NULL;
//                     }
//                     result = new_result;
//                 }

//                 ft_strcpy(result + j, value);
//                 j += value_len;
//             }
//         }
//         else
//         {
//             if (j >= rsult_size) {
//                 rsult_size *= 2; // Duplicar el tamaño si se necesita más espacio
//                 char *new_result = realloc(result, rsult_size + 1);
//                 if (!new_result) {
//                     free(result);
//                     return NULL;
//                 }
//                 result = new_result;
//             }
//             result[j++] = input[i++];
//         }
//     }
//     result[j] = '\0';
//     return result;
// }

//----------------------------------

// void write_heredoc(int fd_file, char *delimiter)
// {
//     char *buffer;
//     ssize_t content;
//     ssize_t cnt;

//     buffer = NULL;
//     while (1)
//     {
//         buffer = readline("> ");
//         if (buffer == NULL || ft_strcmp(buffer, delimiter) == 0)
//         {
//             free(buffer);
//             break;
//         }
//         if (ft_strlen(buffer) > 0)
//         {
//             content = write(fd_file, buffer, ft_strlen(buffer));
//             if (content < 0)
//             {
//                 perror("write to heredoc file");
//                 free(buffer);
//                 exit(EXIT_FAILURE);
//             }
//             cnt = write(fd_file, "\n", 1);
//             if (cnt < 0)
//             {
//                 perror("write to heredoc file");
//                 free(buffer);
//                 exit(EXIT_FAILURE);
//             }
//         }
//         free(buffer);
//     }
// }

// void delete_heredoc(t_params *p)
// {
//     int i;
//     char *rm[4];

//     rm[0] = "/bin/rm";
//     rm[1] = "-f";
//     rm[2] = ".heredoc.tmp";
//     rm[3] = NULL;
//     i = execve("/bin/rm", rm, p->env);
//     if (i < 0)
//     {
//         perror("execve");
//         g_exit_status = 126;
//         exit(126);
//     }
// }

// void handle_heredoc(t_token *data, t_ast *node, t_params *p)
// {
//     int fd_file;
//     int original_stdin;
//     t_redirect_file *heredocs;
//     t_list *heredoc;

//     heredoc = data->infiles;
//     heredocs = (t_redirect_file *)heredoc->content;
//     fd_file = open_heredoc();
//     data = (t_token *)(node->data);
//     write_heredoc(fd_file, heredocs->value);
//     close(fd_file);
//     original_stdin = dup(STDIN_FILENO);
//     if (original_stdin < 0)
//     {
//         perror("dup original stdin");
//         exit(EXIT_FAILURE);
//     }
//     fd_file = open(".heredoc.tmp", O_RDONLY);
//     if (fd_file < 0)
//     {
//         perror("open heredoc file");
//         exit(EXIT_FAILURE);
//     }
//     if (dup2(fd_file, STDIN_FILENO) < 0)
//     {
//         perror("dup2 heredoc");
//         exit(EXIT_FAILURE);
//     }
//     close(fd_file);
//     if (dup2(original_stdin, STDIN_FILENO) < 0)
//     {
//         perror("restore stdin");
//         exit(EXIT_FAILURE);
//     }
//     delete_heredoc(p);
//     close(original_stdin);
// }

