/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 04:25:15 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 14:05:48 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_redirect(t_list *redirect)
{
	t_list	*tmp;
	t_rdi	*content;
	int		fd[2];
	
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	tmp = redirect;
	while (tmp)
	{
		content = tmp->content;
		if (content->type == R_RDR)
			rdr_right(content->target);
		if (content->type == RR_RDR)
			rdr_double_right(content->target);
		else if (content->type == L_RDR)
		{
			if (rdr_left(content->target))
			{
				dup2(fd[0], STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				return (0);
			}
		}
		else if (content->type == LL_RDR)
		 	rdr_double_left(content->target);
		tmp = tmp->next;
	}
	return (1);
}
