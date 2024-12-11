# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 00:49:01 by drestrep          #+#    #+#              #
#    Updated: 2024/12/11 21:13:18 by drestrep         ###   ########.fr        #
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
PATH_SIGNALS	=	./src/signals/
PATH_PIPES		=	./src/pipes/
PATH_BUILT 		=	./src/built_ins/
BASE	   		=	$(addprefix $(PATH_BASE), $(BASE_SRC))
UTILS	   		=	$(addprefix $(PATH_UTILS), $(UTILS_SRC))
PARSING			=	$(addprefix $(PATH_PARSING), $(PARSING_SRC))
SIGNALS			=	$(addprefix $(PATH_SIGNALS), $(SIGNALS_SRC))
PIPES			=	$(addprefix $(PATH_PIPES), $(PIPES_SRC))
BUILT  	  		=	$(addprefix $(PATH_BUILT), $(BUILT_SRC))

BASE_SRC		=	main.c

PARSING_SRC		=	lexer.c \
					parser.c \
					tokenizer.c \
					organize_tokens.c \
					expander.c \
					expand_token.c \
					get_keys.c \
					get_values.c \
					get_nbr_of_keys.c \
					token_utils.c \
					create_args.c \

SIGNALS_SRC		=	handle_signals.c \

PIPES_SRC		=	pipes_util.c \
					validator.c \


BUILT_SRC		=	built_ins1.c \
					built_ins2.c \

UTILS_SRC		=	utils01.c \
					utils02.c \
					utils03.c \
					utils04.c \
					utils05.c \
					utils06.c \
					utils07.c \
					skip_spaces.c \
					remove_quotes.c \
					mem_alloc.c \
					frees01.c \
					gnl.c \

OBJS			=	${PARSING:.c=.o} \
					${SIGNALS:.c=.o} \
					${UTILS:.c=.o} \
					${BASE:.c=.o} \
					${BUILT:.c=.o} \
					${PIPES:.c=.o} \

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) $(INCLUDES)

exe: all
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

clean:
	@rm -rf $(OBJS)
	
fclean: clean	
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
