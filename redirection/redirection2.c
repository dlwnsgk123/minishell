/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 04:25:13 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 14:06:11 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rdr_right(char *target)
{
	int	fd;
	
	fd = open(target, 
				O_CREAT | O_WRONLY | O_TRUNC, 
				S_IRWXU | S_IRWXO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	rdr_double_right(char *target)
{
	int	fd;
	
	fd = open(target, 
				O_CREAT | O_WRONLY | O_APPEND, 
				S_IRWXU | S_IRWXO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int		rdr_left(char *target)
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

void	rdr_double_left(char *target)
{
	int	fd;
	
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXO);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
