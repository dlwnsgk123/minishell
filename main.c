/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 01:39:34 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/23 14:05:19 by junhalee         ###   ########.fr       */
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
	if (!(*input))
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (ft_strlen(*input) != 0)
	{
		if (check_empty(*input))
			add_history(*input);
		tmp = ft_strtrim(*input, " ");
		free(*input);
		*input = tmp;
		return (0);
	}
	else
		return (1);
}

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

void	cmd_clear(t_list **cmd)
{
	t_list	*tmp;
	t_list	*start;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		free_content(&((*cmd)->content));
		ft_lstdelone(*cmd);
		*cmd = tmp;
	}
}

void	sigint_newline(int	signum)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_status = 130;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_env	*env;
	t_list	*cmds;

	input = NULL;
	cmds = NULL;
	env = NULL;
	env_setting(&env, envp);
	while (1)
	{
		echoctl_off();
		signal(SIGINT, sigint_newline);
		signal(SIGQUIT, SIG_IGN);
		if (take_input(&input))
			continue ;
		if (check_input(input) != 0)
			continue ;
		parse(input, &cmds, env);
		echoctl_on();
		if (cmds->next == NULL)
			execute(cmds, &env);
		else
			pipe_execute(cmds, &env);
		cmd_clear(&cmds);
	}
	return (0);
}
