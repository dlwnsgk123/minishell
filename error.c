/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:08:42 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 16:19:29 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char	*str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(strerror((int)errno), STDERR_FILENO);
	exit(1);
}
