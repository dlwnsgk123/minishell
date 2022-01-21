/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:07:37 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/21 19:47:23 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_export(t_env **env)
{
	printf("hi");
}

int	ft_export(char **argv, t_env **env)
{
	if (argv[1] == NULL)
		return (print_export(env));
	if (ft_isalpha(argv[1][0]))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
}
