/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execvp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:11:58 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/25 13:30:25 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_data(t_env *env)
{
	char	*front;
	char	*data;

	front = ft_strjoin(env->key, "=");
	data = ft_strjoin(front, env->value);
	free(front);
	return (data);
}

char	**make_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		len;

	len = env_len(env);
	tmp = env;
	envp = malloc(sizeof(char *) * (len + 1));
	if (envp == NULL)
		exit_error("malloc error");
	len = 0;
	while (tmp)
	{
		envp[len] = make_data(tmp);
		tmp = tmp->next;
		len++;
	}
	envp[len] = NULL;
	return (envp);
}

void	check_path(char *argv)
{
	struct stat	sb;

	if (ft_strchr(argv, '/') == NULL)
		return ;
	if (stat(argv, &sb) < 0)
		err_no_such_file(argv);
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
}

void	path_exec(char **argv, char *env_path, char **envp)
{
	char	**path;
	char	*argv_tmp;
	char	*tmp;
	char	*slash_argv;
	int		i;

	i = 0;
	slash_argv = ft_strjoin("/", argv[0]);
	argv_tmp = argv[0];
	path = ft_split(env_path, ':');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], slash_argv);
		execve(tmp, argv, envp);
		free(tmp);
		i++;
	}
	free(slash_argv);
	free_split(path);
	err_command_not_found(argv_tmp);
}

void	ft_execvp(char **argv, t_env *env)
{
	char	*env_path;
	char	**envp;

	envp = make_envp(env);
	if (execve(argv[0], argv, envp) < 0)
	{
		check_path(argv[0]);
		env_path = env_get_value(&env, "PATH");
		if (env_path == NULL)
			err_no_such_file(argv[0]);
		else
			path_exec(argv, env_path, envp);
	}
}
