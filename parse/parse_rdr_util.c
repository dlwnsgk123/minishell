/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:42:21 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 17:08:04 by junhalee         ###   ########.fr       */
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
	return (0);
}

char	*get_rdi_target(char *str)
{
	char	*start;
	char	*rtn;

	start = str;
	while (*start && ft_strchr(" <>", *str))
	{
		start++;
		str++;
	}
	if (*str == '\'' || *str== '\"')
		str = skip_quote(str);
	while (*str && !ft_strchr(" <>", *str))
			str++;
	rtn = ft_strndup(start, str - start);
	return (rtn);
}

char	*skip_target(char *content)
{
	while (*content && ft_strchr(" <>", *content))
		content++;
	if (*content == '\'' || *content == '\"')
		content = skip_quote(content);
	while (*content && !ft_strchr(" <>", *content))
		content++;
	return (content);
}

t_rdi	*make_rdi(char *content)
{
	t_rdi	*rdi;

	rdi = (t_rdi *)malloc(sizeof(t_rdi));
	if (rdi == NULL)
		exit_error("malloc error: ");
	rdi->type = get_rdi_type(content);
	rdi->target = get_rdi_target(content);
	return (rdi);
}