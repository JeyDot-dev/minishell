/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uber_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:00:22 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/24 15:05:42 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
int		is_meta(const int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

char	*free_join(char *str, char *buffer)
{
	char	*new;

	if (str)
		new = ft_strjoin(str, buffer);
	else
		return (buffer);
	if (!new)
		return (NULL);
	str = ft_memdel(str);
	buffer = ft_memdel(buffer);
	return (new);
}
int		quote_token(char ***splitted_cmd, char *cmd_line, int i)
{
	int		mode;
	int		start;
	char	*buffer;
	char	*final;

	buffer = NULL;
	final = NULL;
	while (cmd_line[i] && (cmd_line[i] == '\'' || cmd_line[i] == '\"'))
	{
		mode = 1;
		if (cmd_line[i] == '\'')
			mode = 2;
		start = ++i;
		while (mode == 1 && cmd_line[i] && cmd_line[i] != '\"')
			i++;
		while (mode == 2 && cmd_line[i] && cmd_line[i] != '\'')
			i++;
		if (cmd_line[i])
		{
			buffer = ft_strndup(&cmd_line[start], i++ - start);
//			if (mode == 1)
//				buffer = expand_string(buffer);
			final = free_join(final, buffer);
		}
		else
			return (free_return_minone(final, "No closing quotes"));
	}
	if (add_to_matrix(splitted_cmd, final) == 0)
		return (i);
	ft_memdel(final);
	return (-1);
}
/*
int		str_token(char ***splitted_cmd, char *cmd_line, int i)
{
	(void) splitted_cmd;
	(void) cmd_line;
	(void) i;
	fprintf(stderr, "str_token\n");
}
int		meta_token(char ***splitted_cmd, char *cmd_line, int i)
{
	(void) splitted_cmd;
	(void) cmd_line;
	(void) i;
	fprintf(stderr, "meta_token\n");
}
int		var_token(char ***splitted_cmd, char *cmd_line, int i, int err)
{
	(void) splitted_cmd;
	(void) cmd_line;
	(void) i;
	(void) err;
	fprintf(stderr, "var_token\n");
}*/
int		create_token(char ***splitted_cmd, char *cmd_line, int i, int err)
{
	(void) err;
//	if (is_meta(cmd_line[i]))
//		i = meta_token(splitted_cmd, cmd_line, i);
	if (cmd_line[i] == '\'' || cmd_line[i] == '\"')
		i = quote_token(splitted_cmd, cmd_line, i);
//	else if (cmd_line[i] == '$')
//		i = var_token(splitted_cmd, cmd_line, i, err);
//	else if (cmd_line[i])
//		i = str_token(splitted_cmd, cmd_line, i);
	return (i);
}

char	**uber_split(char *cmd_line, int err)
{
	char	**splitted_cmd;
	int		i;

	i = 0;
	splitted_cmd = NULL;
	while (cmd_line[i])
	{
		while (cmd_line[i] == 32)
			i++;
		if (cmd_line[i])
			i = create_token(&splitted_cmd, cmd_line, i, err);
		if (i == -1)
		{
			free_matrix(splitted_cmd);
			return (NULL);
		}
	}
	return (splitted_cmd);
}
