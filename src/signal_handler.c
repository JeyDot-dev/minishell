/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:05:48 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 17:05:23 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	handle_sigchild(int sig)
{
	(void)sig;
	while (waitpid(-1, &g_status, 0) > 0)
	{
		g_status = exit_status(g_status);
	}
}

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

int	init_sigint(void (signal_handler)(int, siginfo_t *, void *), int sig)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	if (sigaction(sig, &sa, NULL) == -1)
		return (1);
	return (0);
}
