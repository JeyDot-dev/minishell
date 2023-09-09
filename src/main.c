/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:51:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/09/09 19:59:28 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_cmd(char *cmd, char *arg, char ***env)
{
	char	*arg_tmp[2];

(void)arg;
	if (arg && *arg)
	{
		arg_tmp[0] = arg;
		arg_tmp[1] = NULL;
	}
/*	if (!ft_strncmp(cmd, "pwd", 4))
	{
//		ft_printf ("PWD:");
		ft_pwd();
	}
	else if (!ft_strncmp(cmd, "cd", 3))
	{
//		ft_printf("CD to : %s\n", arg);
	//	ft_cd(arg_tmp, *env);
		test_cmd("PWD", NULL, env);
	}*/
	if (!ft_strncmp(cmd, "env", 4))
		ft_env(*env);
	else if (!ft_strncmp(cmd, "export", 7))
		ft_export(env, arg_tmp);
	else if (!ft_strncmp(cmd, "unset", 6))
		ft_unset(env, arg_tmp);
	else if (!ft_strncmp(cmd, "exit", 5))
	{
		ft_printf(GRN"Exited properly\n"WHT);
		exit(0);
	}
	else
		return (1);
	return (0);
}
int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	int		activ;
	char	*cmd_line;
	char	**tmp_cmd;
	char	**env;

	env = NULL;
	activ = 1;
//	init_env(av, env, &env);
//	ft_printf("-----env2----\n");
//	ft_env2(env);
	while (activ)
	{
		ft_printf(MAG"minishell "CYN"%s " WHT, getvar(env, "PWD"));
		cmd_line = readline(YEL "$ " WHT);
		if (cmd_line && *cmd_line)
		{
			tmp_cmd = ft_split(cmd_line, ' ');
			if (test_cmd(tmp_cmd[0], tmp_cmd[1], &env))
				ft_printf("cmd_line : %s\n", cmd_line);
			free_env(tmp_cmd);
	//		free(cmd_line);
		}
		else
			ft_printf("\n");
	}
	exit(0);
	ft_printf("---printvar (oldpwd, pwd)---\n");
	printvar(envp, "OLDPWD");
	printvar(envp, "PWD");
	exit(0);
}
