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

static int	option_count(char *str)
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

static int	check_option(char **argv)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (argv[i])
	{
		if (option_count(argv[i]) == 0)
			break ;
		i++;
		option++;
	}
	return (option);
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
	option = check_option(argv);
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
