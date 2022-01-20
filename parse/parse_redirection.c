/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:41:29 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/20 17:08:47 by junhalee         ###   ########.fr       */
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
	rdi->type = get_rdi_type(content);
	rdi->target = get_rdi_target(content);
	return (rdi);
}

t_cmd	*get_cmd(char *content)
{
	t_cmd	*cmd;
	char	quote;
	char	*tmp;
	char	*tmp_start;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(content) + 1));
	tmp_start = tmp;
	cmd->argv = NULL;
	cmd->redirect = NULL;
	while (*content != '\0')
	{
		if (*content == '\'' || *content == '\"')
		{
			quote = *content;
			*tmp++ = *content++;
			while (*content != quote)
				if (*content != ' ')
					*tmp++ = *content++;
				else
				{
					*tmp++ = -10;
					content++;
				}
			*tmp++ = *content++;
		}
		else if (*content == '>' || *content == '<')
		{
			ft_lstadd_back(&(cmd->redirect), ft_lstnew(make_rdi(content)));
			content = skip_target(content);
		}
		else
			*tmp++ = *content++;
	}
	*tmp = '\0';
	cmd->argv = ft_split(tmp_start, ' ');
	free(tmp_start);
	return (cmd);
}

void	parse_redirection(t_list **cmds)
{
	char	*tmp;
	t_list	*lst;
	
	lst = *cmds;
	while (lst)
	{
		tmp = ft_strdup((char *)(lst->content));
		free(lst->content);
		lst->content = get_cmd(tmp);
		free(tmp);
		lst = lst->next;
	}
}