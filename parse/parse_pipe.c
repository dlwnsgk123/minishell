/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 10:42:41 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/25 14:15:41 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_pipe(char *input, t_list **cmds)
{
	char	*start;

	start = input;
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
			input = skip_quote(input);
		if (*input == '|')
		{
			ft_lstadd_back(cmds, ft_lstnew(
					ft_strndup(start, input - start)));
			start = input + 1;
		}
		input++;
	}
	ft_lstadd_back(cmds, ft_lstnew(
			ft_strndup(start, input - start)));
}
