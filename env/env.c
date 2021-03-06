/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:50:28 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 16:17:03 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	*get_env_key(char *envp)
{
	int		i;

	i = 0;
	while (envp[i] != '\0')
	{
		if (envp[i] == '=')
			break ;
		i++;
	}
	return (ft_strndup(envp, i));
}

static char	*get_env_value(char *envp)
{
	char	*tmp;

	tmp = ft_strchr(envp, '=');
	return (ft_strdup(tmp + 1));
}

t_env	*ft_envnew(char *envp)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->key = get_env_key(envp);
	env->value = get_env_value(envp);
	env->prev = NULL;
	env->next = NULL;
	return (env);
}

void	env_setting(t_env **env, char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		env_add_back(env, ft_envnew(envp[i]));
		i++;
	}
}
