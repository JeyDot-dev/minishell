/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:05:48 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/30 11:45:39 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	g_status = sig;
}

