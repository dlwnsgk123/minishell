/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:09:51 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/19 11:41:03 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *str)
{
	char	*key;
	char	*start;

	start = str;
	str++;
	if (*(str) == '$')
		key = ft_strdup("$");
	else
	{
		while (*str && !ft_strrchr("\"\'<>|$ ", *(str)))
			str++;
		key = ft_strndup(start + 1, str - start - 1);
	}
	return (key);
}

char	*get_middle(char *str, t_env *env)
{
	char	*start;
	char	*key;
	char	*value;

	key = get_key(str);
	if (*key == '\0')
		return (ft_strdup("$"));
	else if (*key == '?')
		return (ft_itoa(g_status));
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			free(key);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	free(key);
	return (ft_strdup(""));
}

char	*get_last(char *str)
{
	if (*str && ft_strchr("$?", *str))
		str++;
	else
		while (*str && !ft_strrchr("\"\'<>|$ ", *(str)))
			str++;
	return (ft_strdup(str));
}
