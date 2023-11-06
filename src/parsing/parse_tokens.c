/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/06 16:12:56 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// if no cmd/arg found, t_status = 0, if no such file or dire, t_status = 1
/*
{
	int				pipes[2];
	int				fd_out;
	int				fd_in;
	int				run;
	char			**args;
	struct s_cmds	*next;
*/
t_cmds	*create_new_empty_cmd(void)
{
	t_cmds	*new;

	new = malloc(new);
	if (!new)
		fatal_error("malloc error while initiating cmd struct.");
	if (pipe(new->pipe))
		fatal_error("pipe() failed.");
	new->fd_out = 0;
	new->fd_in = 0;
	new->run = 0;
	new->args = NULL;
	new->next = NULL;
	return (new);
}

t_cmds	*init_cmd_struct(int pipes)
{
	t_cmds	*new;
	t_cmds	*previous;
	t_cmds	*new_head;
	int		first;

	first = 1;
	while (pipes >= 0)
	{
		new = create_new_empty_cmd();
		if (first) 
			new_head = new;
		else
			previous->next = new;
		previous = new;
		first = 0;
		pipes--;
	}
	return(new_head);
}
int	open_in_out(t_tokens *tokens, t_io *io, **cmds)
{
	if ((*cmds)->run)
	{
		io->prev_pipe = -1;
		close_pipes(*cmds);
	}
}
t_tokens	*check_in_out(t_io *io, t_tokens *tokens, t_cmds **cmds)
{
	else if (token->is_meta == CHR || token->is_meta == CHRR)
	else if (token->is_meta == CHL || token->is_meta == CHLL)
}
int	set_cmd(t_tokens *tokens, t_cmds **cmds)
int	set_in_out(t_cmds **cmds, t_tokens *tokens)
{
	t_cmds	*tmp_cmds;
	t_io	io;

	io.in = NULL;
	io.out = NULL;
	io.prev_pipe = -1;
	tmp_cmds = *cmds;
	while (tmp_cmds)
	{
		if (tokens->is_meta == PIPE || (tmp_cmds && !tokens))
		{
			io = open_in_out(io, previous_pipe, &tmp_cmds);
			tmp_cmds = tmp_cmds->next;
		}
		else if (tokens->is_meta)
			tokens = check_in_out(&io, tmp_in_out, tokens);
		else if (tokens)
			tokens = set_cmd(tokens, cmds);
	}
	//if -1 -> default_in/out (stdin/stdout) if 2nd pipe or more STDIN = pipe[0] of previous
	//if -2 -> set (*cmds)->run to 1 and go next
}
int	create_cmds_struct(int pipes, t_cmds **cmds)
{
	*cmds = init_cmd_struct(pipes);
}

int	parse_tokens(t_tokens *tokens, t_shell *shell)
{
	(void) tokens;
	(void) shell;
	t_cmds	*cmds;

	cmds = NULL;
	if (create_cmds_struct(count_pipes(tokens), &cmds)) 
	//				count pipes [l/]
	//				create t_cmds [l/]
	//				create pipes (nb pipes + 1) [l/]
	//			while t_cmds
	//				check in/out access and set error in t_cmds
	//						if ^ error repeat last step with next pipe
	//				open in/out files and set them in t_cmds in/out
	//				check if out != 1 if it is, out = next pipe
	//				find cmd and arguments if no cmd/arg > close fd and set error
	return (0);
}
