# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 00:49:01 by drestrep          #+#    #+#              #
#    Updated: 2024/11/13 16:05:50 by igvisera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
					tokenizer.c \
					expander.c

BUILT_SRC		=	built_ins1.c \
					built_ins2.c \

UTILS_SRC		=	utils01.c \
					utils02.c \
					utils03.c \
					utils04.c \
					utils05.c \
					utils06.c \
					mem_alloc.c \
					frees.c \

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
