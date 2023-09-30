/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:08:46 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/30 10:33:57 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	g_status;
// FREE READLINE
int	init_minishell(char **av, char **envp, t_shell **shell)
{
	g_status = 0;
	fprintf(stderr, "WOW\n");
	*shell = malloc(sizeof(*shell));
	if (!shell)
		return (1);
	(*shell)->tokens = NULL;
	init_env(av, envp, &((*shell)->env));
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	if (init_minishell(av, envp, &shell) || g_status)
		exit(1);
	while (ac)
	{
		shell->cmd_line = prompt();
		if (!shell->cmd_line)
			exit(1);
		else
			uber_split(&(shell->tokens), shell->cmd_line, shell->env);
//		if (g_status == 0 && tokens)
		//	parse(tokens
		if (shell->tokens)
			ft_env(shell->tokens);
	}
}
