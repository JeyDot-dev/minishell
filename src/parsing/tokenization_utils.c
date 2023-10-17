/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:43:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/17 14:35:23 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_post_meta_long(char *cmd_line, int i, char sign)
{
	int	ret;

	ret = 42;
	if (cmd_line[i] == sign)
	{
		ret = sign % 60 + 1;
		i++;
	}
	while (cmd_line[i] && cmd_line[i] == 32)
		i++;
	if (cmd_line[i] && !is_meta(cmd_line[i]))
	{
		if (ret != 42)
			return (ret);
		return (sign % 60);
	}
	return (42);
}
void	print_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->token)
			ft_fprintf(2, "[\"%s\" : %i]\n", tokens->token, tokens->is_meta);
		tokens = tokens->next;
	}
}

int	check_post_meta(t_tokens *tokens, char *cmd_line, int i, char sign)
{
	int	ret;

	i++;
	ret = 42;
	if (sign == '|')
	{
		if (!tokens)
			return (ret);
		while (cmd_line[i] && cmd_line[i] == 32)
			i++;
		if (cmd_line[i] && cmd_line[i] != '|')
			return (sign % 60);
	}
	else if (sign == '<' || sign == '>')
		ret = check_post_meta_long(cmd_line, i, sign);
	return (ret);
}

int	find_end_of_token(char *cmd_line, int i, int mode)
{
	while (mode == 1 && cmd_line[i] && cmd_line[i] != '\"')
		i++;
	while (mode == 2 && cmd_line[i] && cmd_line[i] != '\'')
		i++;
	if (mode && !cmd_line[i])
		return (free_return_minone(NULL, "No closing quotes"));
	while (mode == 0 && is_string(cmd_line[i])
		&& cmd_line[i] != '\'' && cmd_line[i] != '\"')
		i++;
	return (i);
}
