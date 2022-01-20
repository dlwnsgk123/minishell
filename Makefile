# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 07:21:51 by junhalee          #+#    #+#              #
#    Updated: 2022/01/20 13:13:40 by junhalee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = #-fsanitize=address

SRCS = main.c \
	env/env.c \
	env/env_util.c \
	check.c \
	parse/parse.c \
	parse/parse_pipe.c \
	parse/parse_redirection.c \
	parse/parse_env.c \
	parse/parse_env_util.c \
	redirection/redirection.c \
	redirection/redirection2.c \
	exec/exec.c \
	echoctl.c \
	builtin/echo.c \
	builtin/cd.c \


INCLUDE	= 

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
		$(MAKE) -s -C ./Libft all
		$(CC) $(CFLAGS) $(OBJS) -L ./Libft -lft -lreadline -o $(NAME)

all : $(NAME)

clean :
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(NAME)

re	: fclean all