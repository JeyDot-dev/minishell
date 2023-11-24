/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:05:48 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/24 17:22:51 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	signal_troll(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig != SIGINT)
		return ;
	g_status = sig;
	ft_fprintf(2, "\n         Wow exiting a here doc with ctrl-c\
...that's... courageous.");
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 1);
	rl_on_new_line();
}

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig != SIGINT)
		return ;
	g_status = sig;
	if (info->si_pid == 0)
		return ;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 1);
	rl_on_new_line();
}
