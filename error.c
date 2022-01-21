/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:08:42 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/21 10:32:25 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char	*str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(1);
}