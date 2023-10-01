/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:08:46 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 11:32:06 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	g_status;
// FREE READLINE
int	init_minishell(char **av, char **envp, t_shell **shell)
{
	g_status = 0;
	*shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	(*shell)->tokens = NULL;
	(*shell)->cmd_line = NULL;
	(*shell)->last_cmd_line = NULL;
	init_env(av, envp, &((*shell)->env));
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	int		tmp_err;

	if (init_minishell(av, envp, &shell) || g_status)
		exit(1);
	while (ac)
	{
		shell->cmd_line = prompt();
		if (!shell->cmd_line)
			exit(1);
//		if (!only_spaces(shell->cmd_line))
		tokenizer(&(shell->tokens), shell->cmd_line, shell->env);
		if (shell->cmd_line)
			update_history(shell);
//		if (g_status == 0 && shell->tokens)
//		{
//		parse(shell->tokens
//		}
		if (shell->tokens)
		{
			tmp_err = builtin_cmd(shell->tokens, &(shell->env));
			if (tmp_err == 777)
				ft_env(shell->tokens);
			else
				g_status = tmp_err;
			free_matrix(shell->tokens);
		}
	}
}
