/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:26:22 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/22 08:34:14 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->value[0] != '\0')
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	ft_env(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	print_env(tmp);
	return (0);
}