/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:21:55 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/26 18:25:29 by seungiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_content(void **content)
{
	int		i;
	t_list	*tmp;
	t_rdi	*rdi;
	t_cmd	*cmd;
	t_list	*rdi_lst;

	cmd = *content;
	rdi_lst = cmd->redirect;
	if (cmd == NULL)
		return ;
	i = -1;
	while ((cmd)->argv[++i])
		free((cmd)->argv[i]);
	free((cmd)->argv);
	while (rdi_lst)
	{
		tmp = rdi_lst->next;
		rdi = rdi_lst->content;
		free(rdi->target);
		free(rdi);
		ft_lstdelone(rdi_lst);
		rdi_lst = tmp;
	}
	free(cmd);
}
