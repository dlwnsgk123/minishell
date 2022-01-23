/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 04:25:42 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 12:47:13 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **argv, t_env **env)
{
	char	*key;

	if (argv[1] == NULL)
		return (0);
	if (ft_isalpha(argv[1][0]) == 0)
	{
		ft_putstr_fd("unset: \'", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\' not a valid identifier\n", 2);
		return (1);
	}
	env_delete_node(argv[1], env);
	return (0);
}
