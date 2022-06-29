/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 04:25:15 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/27 11:46:40 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rdr_right(char *target)
{
	int	fd;

	fd = open(target,
			O_CREAT | O_WRONLY | O_TRUNC,
			S_IRWXU | S_IRWXO);
	if (fd < 0)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_status = 1;
		return (1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			exit_error("dup2 error rdi.c : ");
		close(fd);
	}
	return (0);
}

int	rdr_double_right(char *target)
{
	int	fd;

	fd = open(target,
			O_CREAT | O_WRONLY | O_APPEND,
			S_IRWXU | S_IRWXO);
	if (fd < 0)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_status = 1;
		return (1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			exit_error("dup2 error rdi.c : ");
		close(fd);
	}
	return (0);
}

int	rdr_left(char *target)
{
	int	fd;

	fd = open(target, O_RDONLY, S_IRWXU | S_IRWXO);
	if (fd < 0)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_status = 1;
		return (1);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	reset_fd(int fd[2])
{
	if (dup2(fd[0], STDIN_FILENO) < 0)
		exit_error("reset fd error:");
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		exit_error("reset fd error:");
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	exec_redirect(t_list *redirect, t_env *env)
{
	t_list	*tmp;
	t_rdi	*content;
	int		fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	tmp = redirect;
	while (tmp)
	{
		content = tmp->content;
		if (content->type == R_RDR)
			if (rdr_right(content->target))
				return (reset_fd(fd));
		if (content->type == RR_RDR)
			if (rdr_double_right(content->target))
				return (reset_fd(fd));
		if (content->type == L_RDR)
			if (rdr_left(content->target))
				return (reset_fd(fd));
		if (content->type == LL_RDR)
			rdr_double_left(content->target, env);
		tmp = tmp->next;
	}
	return (1);
}
