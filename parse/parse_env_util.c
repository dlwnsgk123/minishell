/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:09:51 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 13:29:49 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*free_return(char *str, char *key)
{
	free(key);
	return (ft_strdup(str));
}

int	is_end(char c)
{
	if (c == '\'' || c == '\"' || c == '<' || c == '>'
		|| c == '|' || c == '$' || c == -10 || c == ' ')
		return (1);
	else
		return (0);
}

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
		while (*str && !is_end(*str))
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
	if (*key == '\0' && *(str + 1) == ' '
		|| *(str + 1) == '\0' || *(str + 1) == '\"')
		return (free_return("$", key));
	if (*key == '?')
	{
		free(key);
		return (ft_itoa(g_status));
	}
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (free_return(env->value, key));
		env = env->next;
	}
	return (free_return("", key));
}

char	*get_last(char *str)
{
	if (*str != '\0' && ft_strchr("$?", *str))
		str++;
	else
		while (*str != '\0' && !is_end(*str))
			str++;
	return (ft_strdup(str));
}
