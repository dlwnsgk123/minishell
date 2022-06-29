/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:50:14 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/26 19:36:05 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err_rtn(void)
{
	g_status = 2;
	ft_putstr_fd("syntax error\n", STDERR_FILENO);
	return (1);
}

int	check_input(char *input)
{
	if (check_empty(input))
		return (1);
	if (check_quotes(input))
		return (err_rtn());
	if (check_lastchar(input))
		return (err_rtn());
	if (check_near_token(input))
		return (err_rtn());
	if (check_near_token2(input))
		return (err_rtn());
	return (0);
}
