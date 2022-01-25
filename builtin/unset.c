/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 04:25:42 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 21:04:22 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **argv, t_env **env)
{
	int	i;
	int	rtn;

	i = 1;
	rtn = 0;
	if (argv[1] == NULL)
		return (0);
	while (argv[i])
	{
		if (ft_isalpha(argv[i][0]) == 0)
		{
			ft_putstr_fd("unset: \'", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("\' not a valid identifier\n", 2);
			rtn = 1;
		}
		else
			env_delete_node(argv[i], env);
		i++;
	}
	return (rtn);
}
