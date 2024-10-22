# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 18:26:55 by drestrep          #+#    #+#              #
#    Updated: 2024/10/22 04:56:22 by igvisera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= 	minishell

CC 				= 	gcc
CFLAGS 			= 	-g3 -Wall -Wextra -Werror -fsanitize=address -O3
LDFLAGS			=	-lreadline
INCLUDES		= 	-I ./inc/

PATH_BASE 		=	./src/
PATH_UTILS 		=	./src/utils/
PATH_AFD 		=	./src/automaton/
PATH_BUILT 		=	./src/built_ins/
BASE	   		=	$(addprefix $(PATH_BASE), $(BASE_SRC))
UTILS	   		=	$(addprefix $(PATH_UTILS), $(UTILS_SRC))
AFD   	  		=	$(addprefix $(PATH_AFD), $(AFD_SRC))
BUILT  	  		=	$(addprefix $(PATH_BUILT), $(BUILT_SRC))

BASE_SRC		=	main.c

AFD_SRC			=	lexer.c \
					parsing.c \
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
					ft_split.c \
					list_actions.c \

OBJS			=	${AFD:.c=.o} \
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
