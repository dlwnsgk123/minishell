/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:41:29 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 13:43:11 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*make_cmd(char *content)
{
	t_cmd	*cmd;
	char	quote;
	char	*tmp;
	char	*tmp_start;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		exit_error("malloc error");
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(content) + 1));
	if (tmp == NULL)
		exit_error("malloc error");
	tmp_start = tmp;
	cmd->redirect = NULL;
	while (*content != '\0')
	{
		if (*content == '\'' || *content == '\"')
		{
			quote = *content;
			*tmp++ = *content++;
			while (*content != quote)
			{
				if (*content == ' ')
				{
					*tmp++ = -10;
					content++;
				}
				else
					*tmp++ = *content++;
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
	cmd->tmp = tmp_start;
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
		if (tmp == NULL)
			exit_error("malloc error :");
		free(lst->content);
		lst->content = make_cmd(tmp);
		free(tmp);
		lst = lst->next;
	}
}
