/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:03:15 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/20 19:10:07 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_matrix(shell->env);
	if (shell->cmds)
		free_cmds(shell->cmds);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmd_line)
		free(shell->cmd_line);
	if (shell->last_cmd_line)
		free(shell->last_cmd_line);
	free(shell);
}
