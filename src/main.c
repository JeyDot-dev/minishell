/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:08:46 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/14 18:02:20 by jsousa-a         ###   ########.fr       */
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
	if (ac > 1 && ft_strncmp(av[1], "-d", 1) == 0)
		(*shell)->debug = 1;
	else if (ac > 1 && ft_strncmp(av[1], "-v", 1) == 0)
		(*shell)->debug = 2;
	else
		(*shell)->debug = 0;
	(*shell)->tokens = NULL;
	(*shell)->cmd_line = NULL;
	(*shell)->last_cmd_line = NULL;
	init_env(av, envp, &((*shell)->env));
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	fprint_shell(2, *shell, "init_minishell");
	return (0);
}

int	cmd_loop(t_shell *shell)
{
	shell->cmd_line = prompt();
	if (!shell->cmd_line)
		exit(1);
	tokenizer(&(shell->tokens), shell);
	fprint_shell(2, shell, "cmd_loop");
	if (shell->cmd_line)
		update_history(shell);
//		if (shell->tokens)
//			parse(shell->tokens
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
//	int		tmp_err;

	if (init_minishell(ac, av, envp, &shell) || g_status)
		exit(1);
	while (!cmd_loop(shell))
	{
		if (shell->tokens)
		{
			//tmp_err = builtin_cmd(shell->tokens, &(shell->env));
			//if (tmp_err != 777)
//			g_status = tmp_err;
							//!!!!!!!!!!!!!!!!FREE TOKENS
		}
	}
	exit(0);
}
