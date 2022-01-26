/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:51:52 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 12:49:09 by junhalee         ###   ########.fr       */
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

void	env_change_value(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			if (value == NULL)
				return ;
			else
			{
				free(tmp->value);
				tmp->value = value;
				return ;
			}
		}
		tmp = tmp->next;
	}
	tmp = (t_env *)malloc(sizeof(t_env));
	if (tmp == NULL)
		exit_error("malloc error env_util.c : line 68: ");
	tmp->key = ft_strdup(key);
	if (value != NULL)
	{
		tmp->value = ft_strdup(value);
		free(value);
	}
	else
		tmp->value = NULL;
	env_add_back(env, tmp);
}

char	*env_get_value(t_env **env, char *key)
{
	t_env	*tmp;

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
