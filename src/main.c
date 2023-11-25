/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:08:46 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/25 20:32:24 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	g_status;

int	set_exit_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_status = WTERMSIG(status) + 128;
	}
	return (g_status);
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
int	init_minishell(int ac, char **av, char **envp, t_shell **shell)
{
	g_status = 0;
	*shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	if (ac > 1 && ft_strncmp(av[1], "-d", 3) == 0)
		(*shell)->debug = 1;
	else if (ac > 1 && ft_strncmp(av[1], "-v", 3) == 0)
		(*shell)->debug = 3;
	else
		(*shell)->debug = 0;
	(*shell)->tokens = NULL;
	(*shell)->cmd_line = NULL;
	(*shell)->last_cmd_line = NULL;
	init_env(av, envp, &((*shell)->env));
	if (init_sigint(signal_handler, SIGINT))
		return (1);
	signal(SIGQUIT, SIG_IGN);
	fprint_shell(2, *shell, "init_minishell");
	return (0);
}

int	cmd_loop(t_shell *shell)
{
	int	token_status;

	shell->last_cmd_status = g_status;
	if (init_sigint(signal_handler, SIGINT))
		exit (1);
	shell->cmd_line = prompt();
	if (!shell->cmd_line)
	{
//		free_shell(shell);
		exit(0);
	}
	token_status = tokenizer(&(shell->tokens), shell);
	fprint_shell(2, shell, "cmd_loop");
	if (shell->cmd_line)
		update_history(shell);
	if(WIFSIGNALED(g_status))
		g_status = WTERMSIG(g_status) + 128;
	if (!token_status && shell->tokens)
	{
		g_status = 0;
//		delete_tokens(shell->tokens);
//		shell->tokens = NULL;
//		parse_tokens(shell->tokens
	}
	return (0);
}
void	parse_and_execute(t_shell *shell)
{
	parse_tokens(shell->tokens, shell);
	delete_tokens(shell->tokens);
	shell->tokens = NULL;
	if(WIFSIGNALED(g_status))
		g_status = WTERMSIG(g_status) + 128;
	if (shell->cmds)
	{
		if (!g_status)
			g_status = set_exit_status(execute(shell));
		free_cmds(shell->cmds);
	}
	shell->cmds = NULL;
}
//TODO: fix minor prompt error after ctrl+d with heredoc | Hunt for bugs then try to evaluate the project
int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	if (ac > 2 ||
		(ac == 2 &&
		(ft_strncmp(av[1], "-d", 3) != 0 && ft_strncmp(av[1], "-v", 3) != 0)))
	{
		ft_fprintf(2, "minishell: %s: invalid option. Try -d or -v\n", av[1]);
		exit(1);
	}
	shell = NULL;
	if (init_minishell(ac, av, envp, &shell) || g_status)
		exit(1);
	while (!cmd_loop(shell))
	{
		if (shell->tokens)
			parse_and_execute(shell);
	}
	exit(0);
}
