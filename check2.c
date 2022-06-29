/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhalee <junhalee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:26:35 by junhalee          #+#    #+#             */
/*   Updated: 2022/01/26 20:54:16 by junhalee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *input)
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

int	check_near_token(char *input)
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
			if (*input == '<' && *(input + 1) == '<')
				input++;
			input++;
			while (*input == ' ')
				input++;
			if (*input == '|')
				return (1);
		}
		if (*input != '\0')
			input++;
	}
	return (0);
}

int	check_near_token2(char *input)
{
	while (*input)
	{
		if (*input == '\"' || *input == '\'')
			input = skip_quote(input);
		if (input == NULL)
			return (0);
		if (*input == '>' || *input == '<')
		{
			if (*input == '>' && *(input + 1) == '>')
				input++;
			else if (*input == '<' && *(input + 1) == '<')
				input++;
			input++;
			while (*input == ' ')
				input++;
			if (*input == '\0' || *input == '>' || *input == '<')
				return (1);
		}
		input++;
	}
	return (0);
}

int	check_lastchar(char *input)
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
