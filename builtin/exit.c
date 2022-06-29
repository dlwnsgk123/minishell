/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:23:57 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/27 08:53:06 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **argv, int pipe)
{
	if (*(argv + 1) == NULL)
	{
		if (!pipe)
			ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	else if (check_digit(argv[1]) == 0)
	{
		ft_putstr_fd("exit\nexit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (get_argc(argv) > 2)
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		return (1);
	}
	else
	{
		if (!pipe)
			ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(argv[1]));
	}
}
