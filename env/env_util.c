/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:51:52 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/20 16:52:32 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_last(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = env_last(*env);
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	env_change_value(t_env **env, char *key, char *value)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
		free(value);
	}
}

char	*env_get_value(t_env **env, char *key)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (NULL);
}