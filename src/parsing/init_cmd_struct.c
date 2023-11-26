/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 18:40:29 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_cmds	*create_new_empty_cmd(void)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		fatal_error("malloc error while initiating cmd struct.");
	if (pipe(new->pipe))
		fatal_error("pipe() failed.");
	new->fd_out = 1;
	new->fd_in = 0;
	new->run = 0;
	new->is_builtin = 0;
	new->args = NULL;
	new->next = NULL;
	new->path_cmd = NULL;
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
	return (new_head);
}
