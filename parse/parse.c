/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:32:46 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/21 17:30:50 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*skip_quote(char *str)
{
	if (*str == '\'')
		return (ft_strchr(str + 1, '\''));
	else
		return (ft_strchr(str + 1, '\"'));
}

char	*delete_quote(char	*str)
{
	char	quote;
	char	*start_rtn;
	char	*start_str;
	char	*rtn;

	rtn = (char *)malloc(ft_strlen(str) + 5);
	if (rtn == NULL)
		return (NULL);
	start_rtn = rtn;
	start_str = str;
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str;
			str++;
			while (*str != '\0' && *str != quote)
				*rtn++ = *str++;
			if (*str != '\0')
				str++;
		}
		else
			*rtn++ = *str++;
	}
	*rtn = '\0';
	free(start_str);
	return (start_rtn);
}

void	parse(char *input, t_list **cmds, t_env *env)
{
	parse_pipe(input, cmds);
	parse_redirection(cmds);
	parse_env(*cmds, env);
}
