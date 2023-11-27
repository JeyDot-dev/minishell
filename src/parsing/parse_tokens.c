/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/27 03:03:06 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	set_path_cmd(t_cmds *cmds, t_shell *shell)
{
	struct stat	stats;

	stat(cmds->args[0], &stats);
	if (!cmds->args)
	{
		cmds->run = 1;
		return (0);
	}
	if (is_builtin(cmds->args[0]))
		return (1);
	cmds->path_cmd = check_cmd_filetype(cmds, shell);
	return (0);
}

void	set_cmd(t_tokens **tokens, t_cmds *cmds, t_shell *shell)
{
	char	***args;

	args = &cmds->args;
	while (*tokens && !(*tokens)->is_meta)
	{
		add_to_matrix(args, (*tokens)->token);
		*tokens = (*tokens)->next;
	}
	if (!cmds->path_cmd)
		cmds->is_builtin = set_path_cmd(cmds, shell);
}

void	route_and_next(t_cmds **cmds, t_tokens **tokens)
{
	set_fd_to_pipe(*cmds);
	*cmds = (*cmds)->next;
	if (*cmds)
		g_status = 0;
	if (*tokens)
		*tokens = (*tokens)->next;
}

void	parsinator(t_cmds **cmds, t_tokens *tokens, t_shell *shell)
{
	t_cmds		*tmp_cmds;
	t_tokens	*tokens_tmp;

	tmp_cmds = *cmds;
	tokens_tmp = tokens;
	while (g_status != SIGINT && tmp_cmds)
	{
		if ((tokens_tmp && tokens_tmp->is_meta == PIPE) || (
				tmp_cmds && !tokens_tmp))
			route_and_next(&tmp_cmds, &tokens_tmp);
		else if (!tokens_tmp)
			tmp_cmds = NULL;
		else if (tmp_cmds->run)
			tokens_tmp = tokens_tmp->next;
		else if (tokens_tmp->is_meta)
			open_io(&tokens_tmp, &tmp_cmds, shell);
		else
			set_cmd(&tokens_tmp, tmp_cmds, shell);
	}
}

int	parse_tokens(t_tokens *tokens, t_shell *shell)
{
	shell->cmds = init_cmd_struct(count_pipes(tokens));
	parsinator(&shell->cmds, tokens, shell);
	if (g_status == SIGINT)
	{
		fprint_list_cmds(2, *shell, "parsed_tokens");
		free_cmds(shell->cmds);
		shell->cmds = NULL;
	}
	else
		fprint_list_cmds(2, *shell, "parsed_tokens");
	return (0);
}
