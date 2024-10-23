# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 18:26:55 by drestrep          #+#    #+#              #
#    Updated: 2024/10/23 23:47:58 by drestrep         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# SRC_DIR			=		src
# SRCS			=		$(wildcard src/*.c) # POR AHORA

# OBJ_DIR			=		.obj
# OBJS 			= 		$(addprefix .obj/, $(notdir $(SRCS:%.c=%.o)))

# $(NAME):				$(OBJS) | $(OBJ_DIR)
# 						@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

# $(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c | $(OBJ_DIR)
# 						@$(CC) $(CFLAGS) -c $< -o $@

# $(OBJ_DIR):	
# 						@mkdir -p $(OBJ_DIR)


# NAME 			= 	minishell

# CC 				= 	gcc
# CFLAGS 			= 	-g3 -Wall -Wextra -Werror #-fsanitize=address #-O3
# LDFLAGS			=	-lreadline

# PATH_BASE 		=	./src/
# PATH_UTILS 		=	./src/utils/
# PATH_PARSING 		=	./src/automaton/
# BASE	   		=	$(addprefix $(PATH_BASE), $(BASE_SRC))
# PARSING   	  		=	$(addprefix $(PATH_PARSING), $(PARSING_SRC))
# UTILS	   		=	$(addprefix $(PATH_UTILS), $(UTILS_SRC))
# # PATH_PIPES 	=	./src/pipes/
# # PIPES	   		=	$(addprefix $(PATH_PIPES), $(PIPES_SRC))

# # OBJ_DIR 		=	./obj/

# BASE_SRC		=	main.c \

# PARSING_SRC			=	lexer.c \
# 					parsing.c \
# 					tokenizer.c \

# UTILS_SRC		=	utils.c \
# 					utils2.c \

# # PIPES_SRC		=	ft_printf.c \
# # 					ft_printNumbers.c \


# OBJS			=	${PARSING:.c=.o} \
# 					${UTILS:.c=.o} \
# 					${BASE:.c=.o} \
# 					# ${PIPES:.c=.o} \

# all: $(NAME)
# # all: $(OBJ_DIR) $(NAME)


# # $(OBJ_DIR):
# # 	@mkdir -p $(OBJ_DIR)

# $(NAME): $(OBJS)
# 	ar rcs $(NAME) $(OBJS) -o $(NAME) -I ./inc/minishell.h

# clean:
# 	@rm -rf $(OBJS)
	
# fclean: clean	
# 	@rm -rf $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

NAME 			= 	minishell

CC 				= 	gcc
CFLAGS 			= 	-g3 -Wall -Wextra -Werror -fsanitize=address -O3
LDFLAGS			=	-lreadline
INCLUDES		= 	-I ./inc/

PATH_BASE 		=	./src/
PATH_UTILS 		=	./src/utils/
PATH_PARSING	=	./src/parsing/
PATH_BUILT 		=	./src/built_ins/
BASE	   		=	$(addprefix $(PATH_BASE), $(BASE_SRC))
UTILS	   		=	$(addprefix $(PATH_UTILS), $(UTILS_SRC))
PARSING			=	$(addprefix $(PATH_PARSING), $(PARSING_SRC))
BUILT  	  		=	$(addprefix $(PATH_BUILT), $(BUILT_SRC))

BASE_SRC		=	main.c

PARSING_SRC		=	lexer.c \
					parser.c \
					tokenizer.c

BUILT_SRC		=	built_ins1.c \
					built_ins2.c \

UTILS_SRC		=	utils.c \
					utils2.c \
					ft_calloc.c \
					ft_str_toupper.c \
					ft_strchr.c \
					ft_strjoin.c \
					ft_strlcpy.c \
					ft_substr.c \
					split_formated.c \
					ft_strlcat.c \
					ft_strncmp.c \
					frees.c \
					ft_malloc.c \

OBJS			=	${PARSING:.c=.o} \
					${UTILS:.c=.o} \
					${BASE:.c=.o} \
					${BUILT:.c=.o} \

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) $(INCLUDES)

clean:
	@rm -rf $(OBJS)
	
fclean: clean	
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
