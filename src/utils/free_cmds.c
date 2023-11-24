/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:04:58 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/24 21:13:40 by jsousa-a         ###   ########.fr       */
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
			ft_fprintf(2, "freeing args[%d]: %s\n", i, args[i]);
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
		//if (tmp->args)
		//	free_matrix(tmp->args);
		free_args(tmp->args);
		close_pipe(tmp);
		close_fds(tmp->fd_in, tmp->fd_out);
		free(tmp->path_cmd);
		free(tmp);
	}
}
