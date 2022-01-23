/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:42:21 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 13:43:13 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_rdi_type(char *str)
{
	if (*str == '>' && *(str + 1) != '>')
		return (R_RDR);
	if (*str == '>' && *(str + 1) == '>')
		return (RR_RDR);
	if (*str == '<' && *(str + 1) != '<')
		return (L_RDR);
	if (*str == '<' && *(str + 1) == '<')
		return (LL_RDR);
}

char	*get_rdi_target(char *str)
{
	int		i;
	char	*start;
	char	*rtn;

	i = 0;
	start = str;
	while (*start && ft_strchr(" <>", *str))
	{
		start++;
		str++;
	}
	while (*str && !ft_strchr(" <>", *str))
		str++;
	rtn = ft_strndup(start, str - start);
	return (rtn);
}

char	*skip_target(char *content)
{
	while (*content && ft_strchr(" <>", *content))
		content++;
	while (*content && !ft_strchr(" <>", *content))
		content++;
	return (content);
}

t_rdi	*make_rdi(char *content)
{
	t_rdi	*rdi;
	char	*str;

	rdi = (t_rdi *)malloc(sizeof(t_rdi));
	if (rdi == NULL)
		exit_error("malloc error: ");
	rdi->type = get_rdi_type(content);
	rdi->target = get_rdi_target(content);
	return (rdi);
}