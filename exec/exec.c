/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 04:26:20 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/21 12:28:28 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_command_not_found(char *target)
{
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int		is_builtin(char *str)
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

int	exec_builtin(t_cmd	*cmd, t_env **env)
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
	
}

void	process_builtin(t_cmd *cmd, t_env **env, bool pipe)
{
	int		fd[2];

	if (cmd->redirect != NULL)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		if (exec_redirect(cmd->redirect))
		{
			g_status = exec_builtin(cmd, env);
			if (pipe)
				exit(g_status);
			else
			{
				dup2(fd[1], STDOUT_FILENO);
				dup2(fd[0], STDIN_FILENO);
			}
		}
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		g_status = exec_builtin(cmd, env);
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
		if (exec_redirect(cmd->redirect))
		{
			if (execvp(cmd->argv[0], cmd->argv) < 0)
				err_command_not_found(cmd->argv[0]);
		}
	}
	else
		if (execvp(cmd->argv[0], cmd->argv) < 0)
			err_command_not_found(cmd->argv[0]);
}

void	ft_wait()
{
	int	status;

	wait(&status);
	if(WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else
	{
		if (status == SIGINT)
			ft_putstr_fd("\n", 2);
		else if (status == SIGQUIT)
			ft_putstr_fd("Quit\n", 2);
		g_status = WTERMSIG(status) + 128;
	}
}

void	execute(t_list *cmds, t_env **env)
{
	t_list	*tmp;
	t_cmd	*cmd;
	pid_t	pid;

	tmp = cmds;
	cmd = tmp->content;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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

void	pipe_execute(t_list *cmds, t_env **env)
{
	int 	fd[2];
	pid_t	pid;
	int 	fdd;

	return ;
}
