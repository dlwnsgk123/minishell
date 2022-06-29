# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 07:21:51 by junhalee          #+#    #+#              #
#    Updated: 2022/01/27 12:13:43 by junhalee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wextra -Werror -Wall #-fsanitize=address

LDFLAGS=-L/Users/junhalee/.brew/opt/readline/lib

CPPFLAGS=-I/Users/junhalee/.brew/opt/readline/include

SRCS = main.c \
	env/env.c \
	env/env_util.c \
	check.c \
	check2.c \
	error.c \
	util.c \
	parse/parse.c \
	parse/parse_pipe.c \
	parse/parse_rdr.c \
	parse/parse_rdr_util.c \
	parse/parse_env.c \
	parse/parse_env_util.c \
	redirection/redirection.c \
	redirection/redirection2.c \
	exec/exec.c \
	exec/exec_pipe.c \
	exec/exec_util.c \
	exec/execvp.c \
	exec/execvp_util.c \
	exec/macro.c \
	echoctl.c \
	builtin/echo.c \
	builtin/cd.c \
	builtin/pwd.c \
	builtin/env.c \
	builtin/export.c \
	builtin/exit.c \
	builtin/unset.c 

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
		make -C ./Libft all
		$(CC) $(CFLAGS) $(OBJS) $(CPPFLAGS) $(LDFLAGS) -L ./Libft -lft -o $(NAME) -lreadline

all : $(NAME)

clean :
		make -C ./Libft clean
		rm -rf $(OBJS)

fclean : clean
		make -C ./Libft fclean
		rm -rf $(NAME)

re	: fclean all
