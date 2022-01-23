# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 07:21:51 by junhalee          #+#    #+#              #
#    Updated: 2022/01/23 21:05:54 by junhalee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = #-Wextra -Werror -Wall #-fsanitize=address

SRCS = main.c \
	env/env.c \
	env/env_util.c \
	check.c \
	error.c \
	parse/parse.c \
	parse/parse_pipe.c \
	parse/parse_redirection.c \
	parse/parse_redirection_util.c \
	parse/parse_env.c \
	parse/parse_env_util.c \
	redirection/redirection.c \
	redirection/redirection2.c \
	exec/exec.c \
	echoctl.c \
	builtin/echo.c \
	builtin/cd.c \
	builtin/pwd.c \
	builtin/env.c \
	builtin/export.c \
	builtin/exit.c \
	builtin/unset.c 

INCLUDE	= 

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
		$(MAKE) -s -C ./Libft all
		$(CC) $(CFLAGS) $(OBJS) -L ./Libft -lft -o $(NAME) -lreadline

all : $(NAME)

clean :
		rm -rf $(OBJS)

fclean : clean
		rm -rf $(NAME)

re	: fclean all