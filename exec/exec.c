/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 04:26:20 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/25 12:16:22 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(t_cmd	*cmd, t_env **env, bool pipe)
{
	int	builtin;

	builtin = is_builtin(cmd->argv[0]);
	if (builtin == BUILTIN_ECHO)
		return (ft_echo(cmd->argv));
	if (builtin == BUILTIN_CD)
		return (ft_cd(cmd->argv, env));
	if (builtin == BUILTIN_PWD)
		return (ft_pwd());
	if (builtin == BUILTIN_ENV)
		return (ft_env(env));
	if (builtin == BUILTIN_EXPORT)
		return (ft_export(cmd->argv, env));
	if (builtin == BUILTIN_EXIT)
		return (ft_exit(cmd->argv, pipe));
	if (builtin == BUILTIN_UNSET)
		return (ft_unset(cmd->argv, env));
	return (0);
}

void	reset_iofd(int fd[2])
{
	if (dup2(fd[1], STDOUT_FILENO))
		exit_error("STDOUT reset error :");
	if (dup2(fd[0], STDIN_FILENO))
		exit_error("STDIN reset error :");
}

void	process_builtin(t_cmd *cmd, t_env **env, bool pipe)
{
	int		fd[2];

	if (cmd->redirect != NULL)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		if (exec_redirect(cmd->redirect, *env))
		{
			g_status = exec_builtin(cmd, env, pipe);
			if (pipe)
				exit(g_status);
			else
				reset_iofd(fd);
		}
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		g_status = exec_builtin(cmd, env, pipe);
		if (pipe)
			exit(g_status);
	}
}

void	process_binary(t_cmd *cmd, t_env **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->redirect != NULL)
	{
		if (exec_redirect(cmd->redirect, *env))
		{
			if (cmd->argv[0] == NULL)
				exit(0);
			ft_execvp(cmd->argv, *env);
		}
		else
			exit(1);
	}
	else
		ft_execvp(cmd->argv, *env);
}

void	execute(t_list *cmds, t_env **env)
{
	t_list	*tmp;
	t_cmd	*cmd;
	pid_t	pid;

	tmp = cmds;
	cmd = tmp->content;
	if (cmd->argv != NULL && is_builtin(cmd->argv[0]))
		process_builtin(cmd, env, false);
	else
	{
		pid = fork();
		if (pid == 0)
			process_binary(cmd, env);
		else
			ft_wait();
	}
}
