# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 18:26:55 by drestrep          #+#    #+#              #
#    Updated: 2024/09/17 13:27:26 by drestrep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME 			= 		minishell

CC 				= 		gcc
CFLAGS 			= 		-g3 -Wall -Wextra -Werror #-fsanitize=address #-O3
LDFLAGS			=		-lreadline

SRC_DIR			=		src
SRCS			=		$(wildcard src/*.c) # POR AHORA

OBJ_DIR			=		.obj
OBJS 			= 		$(addprefix .obj/, $(notdir $(SRCS:%.c=%.o)))

all:					$(NAME)
	
$(NAME):				$(OBJS) | $(OBJ_DIR)
						@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c | $(OBJ_DIR)
						@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):	
						@mkdir -p $(OBJ_DIR)
	
clean:
						@rm -rf $(OBJ_DIR)
	
fclean: clean	
						@rm -rf $(NAME)

re: fclean all
