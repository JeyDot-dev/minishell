/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/01 12:08:20 by jsousa-a         ###   ########.fr       */
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
t_cmds	create_new_empty_cmd(void)
{
	t_cmds	new;

	if (pipe(new.pipes))
		fatal_error("pipe() failed.");
	new.fd_out = 0;
	new.fd_in = 0;
	new.run = 0;
	new.args = NULL;
	new.next = NULL;
	return (new);
}

t_cmds	*init_cmd_struct(int pipes)
{
	t_cmds	*new;
	t_cmds	*new_head;
	int		first;

	first = 1;
	new = NULL;
	while (pipes >= 0)
	{
		while (!first && new)
			new = new->next;
		new = malloc(new);
		if (!new)
			fatal_error("malloc error while initiating cmd struct.");
		*new = create_new_empty_cmd();
		if (first)
			new_head = new;
		first = 0;
		pipes--;
	}
	return(new_head);
}
int	check_in_out(t_tokens *tokens, t_cmds **cmds)
int	find_cmd(t_tokens *tokens, t_cmds **cmds)
int	set_in_out(t_cmds **cmds, t_tokens *tokens)
{
	int	previous_pipe;
	char	*tmp_in_out[2];

	tmp_in_out[0] = NULL;
	tmp_in_out[1] = NULL;
	previous_pipes = 0;
	while (tokens)
	{
		if (token->is_meta == PIPE)
		{
			open_in_out(tmp_in_out, previous_pipe, cmds);
			previous_pipes = tokens->pipes[0];
			tokens = tokens->next;
		}
		else if (token->is_meta == CHR || token->is_met == CHRR)
		else if (token->is_meta == CHL || token->is_meta == CHLL)
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
