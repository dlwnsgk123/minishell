/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 04:25:42 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 10:02:37 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_delete_node(char *key, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			tmp->prev->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;		
		}
		tmp = tmp->next;
	}
}

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