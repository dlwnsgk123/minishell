/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:07:37 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/25 13:35:17 by junhalee         ###   ########.fr       */
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
	char	*value;

	tmp = ft_strchr(str, '=');
	if (tmp == NULL)
		return (NULL);
	value = ft_strdup(tmp + 1);
	return (value);
}

static int	print_export(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	return (0);
}

int	export_error(int rtn, char *argv)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("\' not a valid identifier\n", 2);
	rtn = 1;
	return (rtn);
}

int	ft_export(char **argv, t_env **env)
{
	char	*key;
	char	*value;
	int		rtn;
	int		i;

	i = 1;
	rtn = 0;
	if (argv[i] == NULL)
		return (print_export(env));
	while (argv[i])
	{
		if (!ft_isalpha(argv[i][0]))
			rtn = export_error(rtn, argv[i]);
		else
		{
			key = get_export_key(argv[i]);
			value = get_export_value(argv[i]);
			env_change_value(env, key, value);
			free(key);
		}
		i++;
	}
	return (rtn);
}
