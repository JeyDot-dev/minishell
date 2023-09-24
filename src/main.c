/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:51:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/09/24 15:02:43 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_shell	*shell;
	char	*cmd_line;
	char	**tmp_cmd;
	char	pwd[PATH_MAX];

	shell = malloc(sizeof(shell));
	if (!shell)
		return (-1);
	shell->env = NULL;
	init_env(av, envp, &shell->env);
	while (ac)
	{
		getcwd(pwd, sizeof(pwd));
		ft_printf(MAG"minishell "CYN"%s " WHT, pwd);
		cmd_line = readline(YEL "$ " WHT);
		if (cmd_line && *cmd_line)
		{
			tmp_cmd = uber_split(cmd_line, 1);
			if (tmp_cmd)
			{
				ft_env(tmp_cmd);
				free_matrix(tmp_cmd);
			}
//			if (builtin_cmd(tmp_cmd, &shell->env) == 777)
//				ft_printf("cmd_line : %s\n", cmd_line);
		}
	}
}
