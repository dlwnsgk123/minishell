/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:23:57 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 16:49:20 by junhalee         ###   ########.fr       */
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

int	ft_exit(char **argv, bool pipe)
{
	if (*(argv + 1) == NULL)
	{
		if (!pipe)
			ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (check_digit(argv[1]) == 0)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(1);
	}
	if (get_argc(argv) > 2)
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		exit(1);
	}
	if (!pipe)
		ft_putstr_fd("exit\n", 2);
	exit(ft_atoi(argv[1]));
}
