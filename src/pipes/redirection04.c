/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection04.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:39:48 by igvisera          #+#    #+#             */
/*   Updated: 2025/02/14 16:24:07 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int open_heredoc(void) {
//     int fd_file = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd_file < 0) {
//         perror("open heredoc");
//         exit(EXIT_FAILURE);
//     }
//     return fd_file;
// }

// void write_to_heredoc(int fd_file, char *buffer) {
//     ssize_t content = write(fd_file, buffer, ft_strlen(buffer));
//     if (content < 0) {
//         perror("write to heredoc file");
//         free(buffer);
//         exit(EXIT_FAILURE);
//     }
//     if (write(fd_file, "\n", 1) < 0) {
//         perror("write to heredoc file");
//         free(buffer);
//         exit(EXIT_FAILURE);
//     }
// }

// void write_heredoc(int fd_file, char *delimiter)
// {
//     char *buffer;
	
// 	buffer = NULL;
//     while (1)
// 	{
//         buffer = readline("> ");
//         if (buffer == NULL || ft_strcmp(buffer, delimiter) == 0) {
//             free(buffer);
//             break;
//         }
//         if (ft_strlen(buffer) > 0)
//             write_to_heredoc(fd_file, buffer);
//         free(buffer);
//     }
// }

// void set_heredoc_input(int fd_file)
// {
//     if (fd_file < 0)
// 	{
//         perror("open heredoc file");
//         exit(EXIT_FAILURE);
//     }
//     unlink(".heredoc.tmp");
//     if (dup2(fd_file, STDIN_FILENO) < 0)
// 	{
//         perror("dup2 heredoc");
//         exit(EXIT_FAILURE);
//     }
//     close(fd_file);
// }

// void handle_heredoc(t_token *data, t_ast *node, t_params *p, t_env *env)
// {
//     pid_t pid;

// 	pid = fork();
//     if (pid < 0)
// 	{
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid == 0) 
// 	{
//         int fd_file;
//         t_redirect_file *heredocs;
//         t_list *heredoc = data->infiles;
//         heredocs = (t_redirect_file *)heredoc->content;
//         fd_file = open_heredoc();
//         write_heredoc(fd_file, heredocs->value);
//         close(fd_file);
//         fd_file = open(".heredoc.tmp", O_RDONLY);
//         set_heredoc_input(fd_file);
//         if (data->cmd != NULL)
//             execute_node(node, p, env);
//         exit(EXIT_SUCCESS);
//     }
// 	else
//         waitpid(pid, &p->status, 0);
// }

// int process_heredoc(t_token *data) {
//     int fd_file;
//     t_list *heredoc = data->infiles;
//     t_redirect_file *heredocs = (t_redirect_file *)heredoc->content;
//     fd_file = open_heredoc();  // Abre el archivo temporal para escritura
//     {
//         char *buffer = NULL;
//         while (1) {
//             buffer = readline("> ");
//             if (buffer == NULL || ft_strcmp(buffer, heredocs->value) == 0) {
//                 free(buffer);
//                 break;
//             }
//             if (ft_strlen(buffer) > 0) {
//                 if (write(fd_file, buffer, ft_strlen(buffer)) < 0) {
//                     perror("write heredoc");
//                     free(buffer);
//                     exit(EXIT_FAILURE);
//                 }
//                 if (write(fd_file, "\n", 1) < 0) {
//                     perror("write heredoc");
//                     free(buffer);
//                     exit(EXIT_FAILURE);
//                 }
//             }
//             free(buffer);
//         }
//     }
//     close(fd_file);
//     fd_file = open(".heredoc.tmp", O_RDONLY);
//     if (fd_file < 0) {
//         perror("open heredoc tmp");
//         exit(EXIT_FAILURE);
//     }
//     return fd_file;
// }

// int open_heredoc(void) {
//     int fd_file = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd_file < 0) {
//         perror("open heredoc");
//         exit(EXIT_FAILURE);
//     }
//     return fd_file;
// }

// void handle_heredoc(t_token *data, t_ast *node, t_params *p, t_env *env) {
//     int hd_fd = process_heredoc(data);
//     if (dup2(hd_fd, STDIN_FILENO) == -1) {
//         perror("dup2 heredoc");
//         exit(EXIT_FAILURE);
//     }
//     /* Elimina el archivo temporal para que no interfiera en ejecuciones posteriores */
//     if (unlink(".heredoc.tmp") == -1) {
//         perror("unlink heredoc");
//         exit(EXIT_FAILURE);
//     }
//     close(hd_fd);
//     /* Ahora, con STDIN redirigido, se ejecuta el comando (o la pipeline) */
//     execute_node(node, p, env);
// }

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	index;
	char	*mem1;
	char	*mem2;

	index = 0;
	if (!src && !dest)
		return (NULL);
	mem1 = ((char *)src);
	mem2 = ((char *)dest);
	if (n == 0)
		return (mem2);
	while (index < n)
	{
		mem2[index] = mem1[index];
		index++;
	}
	return (mem2);
}

void *ft_realloc(void *ptr, size_t new_size)
{
    void *new_ptr;

    if (!new_size)
    {
        free(ptr);
        return NULL;
    }
    new_ptr = ft_malloc(new_size);
    if (!new_ptr)
        return NULL;
    if (ptr)
    {
        ft_memcpy(new_ptr, ptr, new_size);
        free(ptr);
    }
    return (new_ptr);
}

char *ft_strcat(char *dest, const char *src)
{
    char *ptr;

    ptr = dest + ft_strlen(dest);
    while (*src)
        *ptr++ = *src++;
    *ptr = '\0';
    return (dest);
}

char *append_char_to_result(char *result, size_t *buf_size, const char **p)
{
    size_t current_len;
	
    current_len = ft_strlen(result);
    if (current_len + 2 > *buf_size)
    {
        *buf_size *= 2;
        result = ft_realloc(result, *buf_size);
        if (!result)
        {
            perror("ft_realloc");
            exit(EXIT_FAILURE);
        }
    }
    result[current_len] = **p;
    result[current_len + 1] = '\0';
    (*p)++;
    return result;
}

char *expand_variables_heredoc(const char *line, t_env *env)
{
	char *result;
    const char *p;
    size_t len;
    size_t buf_size;

	len = ft_strlen(line);
	buf_size = len * 2 + 1;
	result = ft_malloc(buf_size);
    if (!result)
    {
        perror("ft_malloc");
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';
    p = line;
    while (*p)
    {
        if (*p == '$')
            result = expand_variable_heredoc(&p, env, result, &buf_size);
        else
			result = append_char_to_result(result, &buf_size, &p);
    }
    return (result);
}

int open_heredoc(void)
{
    int fd;

	fd = open(".heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
	{
        perror("open heredoc");
        exit(EXIT_FAILURE);
    }
    return (fd);
}

void write_to_heredoc(int fd_file, char *buffer, t_env *env)
{
    char *expanded;

    if (ft_strlen(buffer) > 0)
    {
        expanded = expand_variables_heredoc(buffer, env);
        free(buffer);
        buffer = expanded;
        if (write(fd_file, buffer, ft_strlen(buffer)) < 0)
        {
            perror("write heredoc");
            free(buffer);
            exit(EXIT_FAILURE);
        }
        if (write(fd_file, "\n", 1) < 0)
        {
            perror("write heredoc");
            free(buffer);
            exit(EXIT_FAILURE);
        }
    }
    free(buffer);
}

int read_heredoc(void)
{
    int fd_file;

    fd_file = open(".heredoc.tmp", O_RDONLY);
    if (fd_file < 0)
    {
        perror("open heredoc tmp");
        exit(EXIT_FAILURE);
    }
    return (fd_file);
}


int process_heredoc(t_token *data, t_env *env)
{
    int fd_file;
    char *buffer;
    t_list *heredoc;
    t_redirect_file *heredocs;

    heredoc = data->infiles;
    heredocs = (t_redirect_file *)heredoc->content;
    fd_file = open_heredoc();
    while (1)
    {
        buffer = readline("> ");
        if (buffer == NULL || ft_strcmp(buffer, heredocs->value) == 0)
        {
            free(buffer);
            break;
        }
        write_to_heredoc(fd_file, buffer, env);
    }
    close(fd_file);
    fd_file = read_heredoc();
    return (fd_file);
}


// int process_heredoc(t_token *data, t_env *env)
// {
//     int fd_file;
//     t_list *heredoc;
//     t_redirect_file *heredocs;
//     heredoc = data->infiles;
// 	heredocs = (t_redirect_file *)heredoc->content;
//     fd_file = open_heredoc();  /* Abre el archivo temporal para escritura */
//     {
//         char *buffer = NULL;
//         while (1)
// 		{
//             buffer = readline("> ");
//             if (buffer == NULL || ft_strcmp(buffer, heredocs->value) == 0)
// 			{
//                 free(buffer);
//                 break;
//             }
//             if (ft_strlen(buffer) > 0)
// 			{
// 				char *expanded;
//                 expanded = expand_variables_heredoc(buffer, env);
//                 free(buffer);
//                 buffer = expanded;
//                 if (write(fd_file, buffer, ft_strlen(buffer)) < 0)
// 				{
//                     perror("write heredoc");
//                     free(buffer);
//                     exit(EXIT_FAILURE);
//                 }
//                 if (write(fd_file, "\n", 1) < 0)
// 				{
//                     perror("write heredoc");
//                     free(buffer);
//                     exit(EXIT_FAILURE);
//                 }
//             }
//             free(buffer);
//         }
//     }
//     close(fd_file);
//     fd_file = open(".heredoc.tmp", O_RDONLY);
//     if (fd_file < 0)
// 	{
//         perror("open heredoc tmp");
//         exit(EXIT_FAILURE);
//     }
//     return fd_file;
// }

void handle_heredoc(t_token *data, t_ast *node, t_params *p, t_env *env)
{
    int hd_fd;
	
    hd_fd = process_heredoc(data, env);
    if (dup2(hd_fd, STDIN_FILENO) == -1)
	{
        perror("dup2 heredoc");
        exit(EXIT_FAILURE);
    }
    if (unlink(".heredoc.tmp") == -1)
	{
        perror("unlink heredoc");
        exit(EXIT_FAILURE);
    }
    close(hd_fd);
	execute_node(node, p, env);
}
