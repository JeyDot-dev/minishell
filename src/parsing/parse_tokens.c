/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/17 18:49:23 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// if no cmd/arg found, t_status = 0, if no such file or dire, t_status = 1
int	parse_tokens(t_tokens *tokens, t_shell *shell)
{
	(void) tokens;
	(void) shell;
	//				count pipes
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
