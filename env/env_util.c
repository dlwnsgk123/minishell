/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:51:52 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/21 15:10:30 by junhalee         ###   ########.fr       */
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

	if (*env == NULL)
	{
		*env = new;
		new->next = NULL;
		return ;
	}
	tmp = env_last(*env);
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
}

void	env_change_value(t_env **env, char *key, char *value)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			free(value);
			return ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (tmp == NULL)
			exit_error("env_util.c : line 68: ");
		tmp->key = ft_strdup(key);
		tmp->value = ft_strdup(value);
		env_add_back(env, tmp);
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