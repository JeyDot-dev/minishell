/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 18:47:33 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	replace_fd(int default_fd, int old_fd, int new_fd)
{
	if (old_fd != default_fd && old_fd != new_fd)
		close(old_fd);
	return (new_fd);
}

int	open_out(t_tokens *tokens, t_cmds **cmds)
{
	if (access(tokens->next->token, F_OK))
		open(tokens->next->token, O_CREAT, 0644);
	if (access(tokens->next->token, W_OK))
	{
		g_status = errno;
	}
	else if (tokens->is_meta == CHR)
		(*cmds)->fd_out = replace_fd(1, (*cmds)->fd_out,
				open(tokens->next->token, O_WRONLY));
	else if (tokens->is_meta == CHRR)
		(*cmds)->fd_out = replace_fd(1, (*cmds)->fd_out,
				open(tokens->next->token, O_WRONLY | O_APPEND));
	if ((*cmds)->fd_out < 0)
	{
		if ((*cmds)->fd_out == -1)
			perror(tokens->next->token);
		return (1);
	}
	return (0);
}

int	open_in(t_tokens *tokens, t_cmds **cmds, t_shell *shell)
{
	if (tokens->is_meta == CHL)
		(*cmds)->fd_in = replace_fd(0, (*cmds)->fd_in,
				open(tokens->next->token, O_RDONLY));
	else if (tokens->is_meta == CHLL)
	{
		(*cmds)->fd_in = replace_fd(0, (*cmds)->fd_in,
				here_doc(tokens->next->token, shell));
		close_pipe(*cmds);
		if (pipe((*cmds)->pipe))
			fatal_error("pipe() failed.");
		(*cmds)->pipe[0] = (*cmds)->fd_in;
	}
	if (g_status == SIGINT)
		return (1);
	if ((*cmds)->fd_in < 0)
	{
		if ((*cmds)->fd_in == -1)
			perror(tokens->next->token);
		g_status = 1;
		return (1);
	}
	return (0);
}

void	open_io(t_tokens **tokens, t_cmds **cmds, t_shell *shell)
{
	if ((*cmds)->run == 1)
		return ;
	else if ((*tokens)->is_meta == CHR || (*tokens)->is_meta == CHRR)
		(*cmds)->run = open_out(*tokens, cmds);
	else if ((*tokens)->is_meta == CHL || (*tokens)->is_meta == CHLL)
		(*cmds)->run = open_in(*tokens, cmds, shell);
	*tokens = (*tokens)->next->next;
}
