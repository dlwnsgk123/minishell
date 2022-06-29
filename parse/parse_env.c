/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:59:46 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/27 08:49:14 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_env(char *str, char *start, t_env *env, int in_dquote)
{
	char	*first;
	char	*middle;
	char	*last;
	char	*front;
	char	*back;

	first = ft_strndup(start, str - start);
	middle = get_middle(str, env);
	last = get_last(str + 1);
	front = ft_strjoin(first, middle);
	back = parse_env_start(last, env, in_dquote);
	free(start);
	start = ft_strjoin(front, back);
	free(middle);
	free(first);
	free(front);
	free(back);
	return (start);
}

char	*parse_env_start(char *str, t_env *env, int in_dquote)
{
	char	*start;

	start = str;
	while (*str != '\0')
	{
		if (*str == '\"')
			in_dquote = !in_dquote;
		else if (*str == '\'' && in_dquote == 0)
			str = skip_quote(str);
		if (*str == '$')
			return (replace_env(str, start, env, in_dquote));
		str++;
	}
	return (start);
}

void	parse_env(t_list *cmds, t_env *env)
{
	t_list	*tmp;
	t_cmd	*cmd;
	t_rdi	*rdi;
	t_list	*rdi_lst;

	tmp = cmds;
	while (tmp)
	{
		cmd = tmp->content;
		rdi_lst = cmd->redirect;
		if (rdi_lst != NULL)
		{
			while (rdi_lst)
			{
				rdi = rdi_lst->content;
				rdi->target = delete_quote(\
							parse_env_start(rdi->target, env, 0));
				rdi_lst = rdi_lst->next;
			}
		}
		cmd->tmp = delete_quote(parse_env_start(cmd->tmp, env, 0));
		cmd->argv = ft_split(cmd->tmp, ' ');
		free(cmd->tmp);
		tmp = tmp->next;
	}
}
