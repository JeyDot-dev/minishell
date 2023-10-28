/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/28 14:44:51 by jsousa-a         ###   ########.fr       */
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
/*
t_cmds	*init_cmd_struct(void)
{
	t_cmds	*new;

	new = malloc(new);
	if (!new)
		return (NULL);
	if (pipe(new->pipes))
		fatal_error("pipe() failed.");
}
int	find_in_out(t_tokens *tokens, int in_out, t_cmds **cmds)
int	find_cmd(t_tokens *tokens, t_cmds **cmds)
int	set_in_out(t_cmds **cmds)
{
}
int	create_cmds_struct(int pipes, t_cmds **cmds)
{
	t_cmds	*tmp;

	while (pipes >= 0)
	{
		tmp = malloc(t_cmds);
		pipes--;
	}
}
*/
int	parse_tokens(t_tokens *tokens, t_shell *shell)
{
	(void) tokens;
	(void) shell;
	//				count pipes [l/]
	//				create t_cmds
	//				create pipes (nb pipes + 1)
	//			while t_cmds
	//				check in/out access and set error in t_cmds
	//						if ^ error repeat last step with next pipe
	//				open in/out files and set them in t_cmds in/out
	//				check if out != 1 if it is, out = next pipe
	//				find cmd and arguments if no cmd/arg > close fd and set error
	return (0);
}
