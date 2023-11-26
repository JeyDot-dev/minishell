/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_to_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 18:54:42 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	set_fd_to_pipe(t_cmds *cmds)
{
	if (cmds->run == 1)
	{
		close_pipe(cmds);
		if (cmds->fd_in != STDIN_FILENO)
			close(cmds->fd_in);
		if (cmds->fd_out != STDOUT_FILENO)
			close(cmds->fd_out);
	}
	if (cmds->fd_out == 1 && cmds->next)
	{
		cmds->fd_out = cmds->next->pipe[1];
		cmds->next->fd_in = cmds->next->pipe[0];
	}
	else if (cmds->next)
		close(cmds->next->pipe[1]);
}
