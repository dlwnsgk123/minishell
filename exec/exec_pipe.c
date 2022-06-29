/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 07:47:17 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/27 11:52:29 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_wait(int last_pid)
{
	int	status;
	int	last_status;
	int	pid;

	while (1)
	{
		pid = wait(&status);
		if (pid == last_pid)
			last_status = status;
		if (pid < 0)
			break ;
	}
	if (status == SIGINT || last_status == SIGINT)
		ft_putstr_fd("\n", 2);
	else if (status == SIGQUIT || last_status == SIGINT)
		ft_putstr_fd("Quit : 3\n", 2);
	if (ft_wifexited(last_status))
		g_status = ft_wexitstatus(last_status);
	else
		g_status = last_status + 128;
}

void	child_execute(t_list *tmp, t_env **env, int fd[2], int fd_in)
{
	t_cmd	*cmd;

	cmd = tmp->content;
	if (dup2(fd_in, STDIN_FILENO) < 0)
		exit_error("dup2 error: ");
	if (tmp->next != NULL)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			exit_error("dup2 error: ");
	}
	close(fd[0]);
	if (is_builtin(cmd->argv[0]))
		process_builtin(cmd, env, 1);
	else
		process_binary(cmd, env);
}

void	parent_process(int fd[], int fd_in)
{
	close(fd[1]);
	if (dup2(fd[0], fd_in) < 0)
		exit_error("dup2 error :");
	close(fd[0]);
}

void	pipe_execute(t_list *cmds, t_env **env)
{
	int		fd[2];
	int		fd_in;
	t_list	*tmp;
	int		pid;
	int		last_pid;

	tmp = cmds;
	fd_in = dup(0);
	while (tmp != NULL)
	{
		pipe(fd);
		pid = fork();
		if (tmp->next == NULL)
			last_pid = pid;
		if (pid == 0)
			child_execute(tmp, env, fd, fd_in);
		else
		{
			parent_process(fd, fd_in);
			tmp = tmp->next;
		}
	}
	pipe_wait(last_pid);
	close(fd_in);
}
