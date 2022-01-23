/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:07:37 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 09:35:02 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_export_key(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (ft_strndup(str, i));
}

static char	*get_export_value(char *str)
{
	char	*tmp;

	tmp = strchr(str, '=');
	if (tmp == NULL)
		return (ft_strdup(""));
	return (ft_strdup(tmp + 1));
}

static int	print_export(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->value[0] != '\0')
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_export(char **argv, t_env **env)
{
	char *key;
	char *value;

	if (argv[1] == NULL)
		return (print_export(env));
	if (!ft_isalpha(argv[1][0]))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\' not a valid identifier\n", 2);
		return (1);
	}
	else
	{
		key = get_export_key(argv[1]);
		value = get_export_value(argv[1]);
		env_change_value(env, key, value);
		free(key);
	}
	return (0);
}
