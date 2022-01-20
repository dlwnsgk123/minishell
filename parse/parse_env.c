/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:59:46 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/16 10:15:01 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_env(char *str, char *start, t_env *env, bool in_dquote)
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
	return (delete_quote(start));
}

char	*parse_env_start(char *str, t_env *env, bool in_dquote)
{
	char	*start;

	start = str;
	while (*str)
	{
		if (*str == '\"')
			in_dquote = !in_dquote;
		else if (*str == '\'' && in_dquote == false)
			str = skip_quote(str);
		if (*str == '$')
			return (replace_env(str, start, env, in_dquote));
		str++;
	}
	return (delete_quote(start));
}

void	*parse_env(t_list *cmds, t_env *env)
{
	t_list	*tmp;
	t_cmd	*cmd;
	t_rdi	*rdi;
	t_list	*rdi_lst;
	int		i;

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
				rdi->target = parse_env_start(rdi->target, env, false);
				rdi_lst = rdi_lst->next;
			}
		}
		i = -1;
		while (cmd->argv[++i])
			cmd->argv[i] = parse_env_start(cmd->argv[i], env, false);
		tmp = tmp->next;
	}
}
