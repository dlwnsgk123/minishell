/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:01:56 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/20 16:28:04 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_argc(char **argv)
{
	int		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

char	*get_newpath(char *str, t_env **env)
{
	if (str == NULL)
		return (env_get_value(env, "HOME"));
	else if (*str == '~')
		return (env_get_value(env, "HOME"));
	else if (*str == '-')
		return (env_get_value(env, "OLDPWD"));
	else
		return (ft_strdup(str));
}

int	ft_cd(char **argv, t_env **env)
{
	char	*oldpath;
	char	*newpath;

	if (get_argc(argv) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	newpath = get_newpath(argv[1], env);
	if (newpath == NULL)
	{
		ft_putstr_fd("cd: OLDPWD not set", STDERR_FILENO);
		return (1);
	}
	oldpath = getcwd(NULL, 0);
	if (chdir(newpath) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(newpath, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free(newpath);
		free(oldpath);
		return (1);
	}
	free(newpath);
	free(oldpath);
	return (0);
}