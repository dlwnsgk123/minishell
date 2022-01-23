/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:19:39 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 12:45:56 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	else
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_echo(char **argv)
{
	int	i;
	int	option;

	i = 1;
	if (argv[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	option = check_option(argv[i]);
	i += option;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
