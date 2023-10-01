/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:00:22 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 18:20:46 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_string(char *cmd_line, char **buffer, int i, char **env)
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
		*buffer = expand_string(*buffer, env);
	if (start[1])
		i++;
	return (i);
}

int	str_token(char ***split_cmds, char *cmd_line, int i, char **env)
{
	char	*new_str;
	char	*buffer;

	new_str = NULL;
	while (is_string(cmd_line[i]))
	{
		buffer = NULL;
		i = get_string(cmd_line, &buffer, i, env);
		if (i >= 0)
			new_str = free_join(new_str, buffer);
	}
	if (new_str && add_to_matrix(split_cmds, new_str) != 0)
		i = -1;
	ft_memdel(new_str);
	return (i);
}

int	meta_token(char ***split_cmds, char *cmd_line, int i)
{
	int	j;

	j = check_post_meta(*split_cmds, cmd_line, i, cmd_line[i]);
	if (j == 42)
	{
		ft_putstr_fd("Error near ", 2);
		ft_putchar_fd(cmd_line[i], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	i++;
	if (j == 0)
		add_to_matrix(split_cmds, "<");
	if (j == 1)
		add_to_matrix(split_cmds, "<<");
	if (j == 2)
		add_to_matrix(split_cmds, ">");
	if (j == 3)
		add_to_matrix(split_cmds, ">>");
	if (j == 4)
		add_to_matrix(split_cmds, "|");
	if (j == 3 || j == 1)
		i++;
	return (i);
}

int	tokenizer(char	***split_cmds, t_shell *shell)
{
	int		i;

	i = 0;
	*split_cmds = NULL;
	while (shell->cmd_line[i])
	{
		while (shell->cmd_line[i] && shell->cmd_line[i] == 32)
			i++;
		if (is_meta(shell->cmd_line[i]))
			i = meta_token(split_cmds, shell->cmd_line, i);
		else if (shell->cmd_line[i])
			i = str_token(split_cmds, shell->cmd_line, i, shell->env);
		if (i == -1)
		{
			if (*split_cmds)
				free_matrix(*split_cmds);
			*split_cmds = NULL;
			g_status = 2;
			return (2);
		}
	}
	return (0);
}
