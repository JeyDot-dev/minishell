/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:08:46 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/27 03:07:00 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	g_status;

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
		ft_putchar_fd('\n', 2);
		ft_exit(NULL, shell);
	}
	token_status = tokenizer(&(shell->tokens), shell);
	fprint_shell(2, shell, "cmd_loop");
	if (shell->cmd_line)
		update_history(shell);
	if (WIFSIGNALED(g_status))
		g_status = WTERMSIG(g_status) + 128;
	if (!token_status && shell->tokens)
	{
		g_status = 0;
	}
	return (0);
}

void	parse_and_execute(t_shell *shell)
{
	parse_tokens(shell->tokens, shell);
	delete_tokens(shell->tokens);
	shell->tokens = NULL;
	if (g_status == SIGINT)
		g_status = 130;
	if (shell->cmds)
	{
		g_status = execute(shell);
		free_cmds(shell->cmds);
	}
	shell->cmds = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	if (ac > 2 || (
			ac == 2 && (ft_strncmp(av[1], "-d", 3) != 0
				&& ft_strncmp(av[1], "-v", 3) != 0)))
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
