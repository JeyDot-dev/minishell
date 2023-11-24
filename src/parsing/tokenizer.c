/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:00:22 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/24 17:31:14 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_string(char *cmd_line, char **buffer, int i, t_shell *shell)
{
	int	start[2];

	start[0] = i;
	start[1] = 0;
	if (cmd_line[i] == '\"' || cmd_line[i] == '\'')
	{
		start[1] = 1;
		if (cmd_line[i] == '\'')
			start[1] = 2;
		start[0] = ++i;
	}
	else
		start[1] = 0;
	i = find_end_of_token(cmd_line, i, start[1]);
	if (i < 0)
		return (i);
	*buffer = ft_strndup(&(cmd_line[start[0]]), i - start[0]);
	if (start[1] == 0 || start[1] == 1)
		*buffer = expand_string(*buffer, shell);
	if (start[1])
		i++;
	return (i);
}

int	str_token(t_tokens **tokens, char *cmd_line, int i, t_shell *shell)
{
	char	*new_str;
	char	*buffer;

	new_str = NULL;
	while (is_string(cmd_line[i]))
	{
		buffer = NULL;
		i = get_string(cmd_line, &buffer, i, shell);
		if (i >= 0)
			new_str = free_join(new_str, buffer);
	}
	if (new_str && add_token(ft_strdup(new_str), 0, tokens) != 0)
		i = -1;
	ft_memdel(new_str);
	return (i);
}

int	meta_token(t_tokens **tokens, char *cmd_line, int i)
{
	int	j;

	j = check_post_meta(*tokens, cmd_line, i, cmd_line[i]);
	if (j == 42)
	{
		ft_putstr_fd("Error near ", 2);
		ft_putchar_fd(cmd_line[i], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	i++;
	if (j == 0)
		add_token(ft_strdup("<"), j + 1, tokens);
	if (j == 1)
		add_token(ft_strdup("<<"), j + 1, tokens);
	if (j == 2)
		add_token(ft_strdup(">"), j + 1, tokens);
	if (j == 3)
		add_token(ft_strdup(">>"), j + 1, tokens);
	if (j == 4)
		add_token(ft_strdup("|"), j + 1, tokens);
	if (j == 3 || j == 1)
		i++;
	return (i);
}

int	tokenizer(t_tokens **tokens, t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->cmd_line[i])
	{
		while (shell->cmd_line[i] && shell->cmd_line[i] == 32)
			i++;
		if (is_meta(shell->cmd_line[i]))
			i = meta_token(tokens, shell->cmd_line, i);
		else if (shell->cmd_line[i])
			i = str_token(tokens, shell->cmd_line, i, shell);
		if (i == -1)
		{
			delete_tokens(*tokens);
			*tokens = NULL;
			g_status = 2;
			return (2);
		}
	}
	return (0);
}
