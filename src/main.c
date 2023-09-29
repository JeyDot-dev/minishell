/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:08:46 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/29 18:48:24 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	g_status;
// FREE READLINE
int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_shell	*shell;
	char	**tmp_cmd;
	char	*cmd_line;

	g_status = 0;
	shell = malloc(sizeof(shell));
	if (!shell)
		return (-1);
	init_env(av, envp, &shell->env);
	tmp_cmd = NULL;
	while (ac)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		cmd_line = prompt();
		if (!cmd_line)
			exit(0); //temporary (has to return 1 etc.., free env)
		else
			uber_split(&tmp_cmd, cmd_line, shell->env);
		if (tmp_cmd)
			ft_env(tmp_cmd);
//			if (builtin_cmd(tmp_cmd, &shell->env) == 777)
//				ft_printf("cmd_line : %s\n", cmd_line);
	}
}
