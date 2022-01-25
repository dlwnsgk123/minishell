/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execvp_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:29:42 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/25 12:36:48 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_no_such_file(char *argv)
{
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

void	err_command_not_found(char *target)
{
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int	env_len(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
