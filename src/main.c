/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:08:46 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/20 19:33:39 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	g_status;

int	init_sigint(void (signal_handler)(int, siginfo_t *, void *), int sig)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = signal_handler;
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
		(*shell)->debug = 2;
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
	shell->cmd_line = prompt();
	if (!shell->cmd_line)
		exit(1);
	token_status = tokenizer(&(shell->tokens), shell);
	if (shell->cmd_line)
		update_history(shell);
	if (!token_status && shell->tokens)
	{
		g_status = 0;
//		delete_tokens(shell->tokens);
//		shell->tokens = NULL;
//		parse_tokens(shell->tokens
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	if (init_minishell(ac, av, envp, &shell) || g_status)
		exit(1);
	while (!cmd_loop(shell))
	{
		if (shell->tokens)
		{
			parse_tokens(shell->tokens, shell);
			delete_tokens(shell->tokens);
			shell->tokens = NULL;
			execute(shell);
			if (shell->cmds)
				free_cmds(shell->cmds);
			shell->cmds = NULL;
			//tmp_err = builtin_cmd(shell->tokens, &(shell->env));
			//if (tmp_err != 777)
//			g_status = tmp_err;
							//!!!!!!!!!!!!!!!!FREE TOKENS AND cmds and set cmds to NULL!!!!!!!!!!!!!!!!!!!!
		}
	}
	exit(0);
}
