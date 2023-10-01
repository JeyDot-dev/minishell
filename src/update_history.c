/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:30:37 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 11:31:10 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	update_history(t_shell *shell)
{
		fprintf(stderr, "TEST\n");
	if (!only_spaces(shell->cmd_line) && ft_strncmp(shell->last_cmd_line,
			shell->cmd_line, ft_strlen(shell->cmd_line)))
	{
		add_history(shell->cmd_line);
		if (shell->last_cmd_line)
			ft_memdel(shell->last_cmd_line);
		shell->last_cmd_line = shell->cmd_line;
		shell->cmd_line = NULL;
	}
	else
		ft_memdel(shell->cmd_line);
}
