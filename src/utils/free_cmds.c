/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:04:58 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/24 21:28:05 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		if (ft_strncmp(args[i], "minishell", 10) &&
			ft_strncmp(args[i], "./minishell", 12))
		{
			free(args[i]);
		}
		i++;
	}
	free(args);
}
void	free_cmds(t_cmds *cmds)
{
	t_cmds	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_args(tmp->args);
		close_pipe(tmp);
		close_fds(tmp->fd_in, tmp->fd_out);
		free(tmp->path_cmd);
		free(tmp);
	}
}
