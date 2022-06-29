/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 08:39:05 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/27 10:50:18 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_wtermsig(int	status)
{
	return (status & 0x7f);
}

int	ft_wifexited(int status)
{
	return (ft_wtermsig(status) == 0);
}

int	ft_wexitstatus(int status)
{
	return (((status) & 0xff00) >> 8);
}

/*
0x7f = 			  1111111
0xff00 = 1111111100000000
*/