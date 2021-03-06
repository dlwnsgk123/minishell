/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 04:25:13 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/27 08:51:47 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		input = parse_env_start(input, env, 0);
		ft_putendl_fd(input, fd);
		free(input);
	}
	free(input);
	close(fd);
	rdr_left(".heredoc");
}
