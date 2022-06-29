/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 01:39:34 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/26 18:24:55 by seungiki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	take_input(char **input)
{
	char	*tmp;

	if (*input != NULL)
		free(*input);
	*input = readline("minishell$ ");
	if ((*input) == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (ft_strlen(*input) != 0)
	{
		if (check_empty(*input) == 0)
			add_history(*input);
		else
			return (1);
		tmp = ft_strtrim(*input, " ");
		free(*input);
		*input = tmp;
		return (0);
	}
	else
		return (1);
}

void	cmd_clear(t_list **cmd)
{
	t_list	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		free_content(&((*cmd)->content));
		ft_lstdelone(*cmd);
		*cmd = tmp;
	}
}

void	sigint_newline(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_status = 1;
}

static void	main_loop(t_list **cmds, t_env **env, char *input)
{
	while (1)
	{
		echoctl_off();
		signal(SIGINT, sigint_newline);
		signal(SIGQUIT, SIG_IGN);
		if (take_input(&input))
			continue ;
		if (check_input(input) != 0)
			continue ;
		parse(input, cmds, *env);
		echoctl_on();
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if ((*cmds)->next == NULL)
			execute((*cmds), env);
		else
			pipe_execute((*cmds), env);
		unlink(".heredoc");
		cmd_clear(cmds);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_env	*env;
	t_list	*cmds;

	input = NULL;
	cmds = NULL;
	env = NULL;
	(void)argv;
	(void)argc;
	env_setting(&env, envp);
	main_loop(&cmds, &env, input);
	return (0);
}
