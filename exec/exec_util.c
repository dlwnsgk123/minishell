/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 07:51:21 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/25 12:35:56 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_wait(void)
{
	int	status;
	int	pid;

	pid = wait(&status);
	if (pid < 0)
		return (-1);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else
	{
		if (status == SIGINT)
			ft_putstr_fd("\n", 2);
		else if (status == SIGQUIT)
			ft_putstr_fd("Quit\n", 2);
		g_status = WTERMSIG(status) + 128;
	}
	return (pid);
}

int	is_builtin(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strcmp(str, "exit") == 0)
		return (BUILTIN_EXIT);
	else if (ft_strcmp(str, "cd") == 0)
		return (BUILTIN_CD);
	else if (ft_strcmp(str, "echo") == 0)
		return (BUILTIN_ECHO);
	else if (ft_strcmp(str, "export") == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strcmp(str, "unset") == 0)
		return (BUILTIN_UNSET);
	else if (ft_strcmp(str, "env") == 0)
		return (BUILTIN_ENV);
	else if (ft_strcmp(str, "pwd") == 0)
		return (BUILTIN_PWD);
	else
		return (0);
}
