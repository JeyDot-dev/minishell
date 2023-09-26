/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:51:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/09/26 10:50:19 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_shell	*shell;
	char	**tmp_cmd;
	char	pwd[PATH_MAX];

	shell = malloc(sizeof(shell));
	if (!shell)
		return (-1);
	shell->env = NULL;
	shell->err = 0;
	init_env(av, envp, &shell->env);
	while (ac)
	{
		tmp_cmd = NULL;
		getcwd(pwd, sizeof(pwd));
		ft_printf(MAG"minishell "CYN"%s " WHT, pwd);
		shell->err = uber_split(&tmp_cmd, readline(YEL "$ " WHT), shell->err, shell->env);
		if (tmp_cmd)
		{
			ft_env(tmp_cmd);
			free_matrix(tmp_cmd);
		}
//			if (builtin_cmd(tmp_cmd, &shell->env) == 777)
//				ft_printf("cmd_line : %s\n", cmd_line);
	}
}
