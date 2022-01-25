/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 04:25:13 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/24 18:10:51 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*rdr_replace(char *str, char *start, t_env *env, bool in_dquote)
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

static char	*rdr_parse_env(char *str, t_env *env, bool in_dquote)
{
	char	*start;

	start = str;
	while (*str != '\0')
	{
		if (*str == '\"')
			in_dquote = !in_dquote;
		else if (*str == '\'' && in_dquote == false)
			str = skip_quote(str);
		if (*str == '$')
			return (rdr_replace(str, start, env, in_dquote));
		str++;
	}
	return (start);
}

void	rdr_double_left(char *target, t_env *env)
{
	int		fd;
	char	*input;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXO);
	if (fd < 0)
		exit_error("heredoc make error :");
	while (1)
	{
		input = readline("> ");
		if (input == NULL || ft_strcmp(input, target) == 0)
			break ;
		ft_putendl_fd(rdr_parse_env(input, env, false), fd);
		free(input);
	}
	free(input);
	close(fd);
	rdr_left(".heredoc");
}
