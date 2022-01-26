/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 09:50:14 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/25 13:20:41 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *input)
{
	while (*input)
	{
		if (*input == '\"')
			input = ft_strchr(input + 1, '\"');
		if (input == NULL)
			return (1);
		if (*input == '\'')
			input = ft_strchr(input + 1, '\'');
		if (input == NULL)
			return (1);
		input++;
	}
	return (0);
}

static int	check_near_token(char *input)
{
	while (*input)
	{
		if (*input == '\"' || *input == '\'')
			input = skip_quote(input);
		if (input == NULL)
			return (0);
		else if (ft_strchr("><|", *input))
		{
			if (*input == '>' && *(input + 1) == '>')
				input++;
			else if (*input == '<' && *(input + 1) == '<')
				input++;
			input++;
			while (*input == ' ')
				input++;
			if (ft_strchr("><|", *input))
				return (1);
		}
		input++;
	}
	return (0);
}

static int	check_lastchar(char *input)
{
	int	len;

	len = ft_strlen(input);
	if (ft_strchr(">|", input[len - 1]))
		return (1);
	else
		return (0);
}

int	check_empty(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_input(char *input)
{
	if (check_empty(input))
		return (1);
	if (check_quotes(input))
	{
		g_status = 2;
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		return (1);
	}
	if (check_lastchar(input))
	{
		g_status = 2;
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		return (1);
	}
	 if (check_near_token(input))
	{
		g_status = 2;
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		return (1);
	}
	else
		return (0);
}
