/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:51:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/09/08 15:25:18 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env2(t_env *env)
{
	while (env)
	{
		printvar(env);
		env = env->next;
	}
}
void	test_cmd(char *cmd, char *arg, t_env *env)
{
	char *arg_tmp[2];

	if (arg && *arg)
		arg_tmp[1] = arg;
	if (!ft_strncmp(cmd, "PWD", 3))
	{
		ft_printf ("PWD:");
		ft_pwd();
	}
	if (!ft_strncmp(cmd, "CD", 2))
	{
		ft_printf("CD to : %s\n", arg);
		ft_cd(arg_tmp, env);
		test_cmd("PWD", NULL, env);
	}
	if (!ft_strncmp(cmd, "ENV", 3))
	{
		ft_printf("-----ENV-----\n");
		ft_env2(env);
	}
}
int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) envp;
	t_env	*env;
	int		activ;
	char	*cmd_line;

	activ = 1;
	env = NULL;
	init_env(av, envp, &env);
//	ft_printf("-----env2----\n");
//	ft_env2(env);
	while (activ)
	{
		ft_printf(CYN "minishell :) %s" WHT, getvar(env, "PWD")->data);
		cmd_line = readline(">");
		if (cmd_line && *cmd_line)
			ft_printf("cmd_line : %s\n", cmd_line);
		else
			activ = 0;
		ft_memdel(cmd_line);
	}
	ft_printf(GRN"Exited properly\n"WHT);
	exit(0);
	ft_printf("-----printvar----\n");
	printvar(getvar(env, "HOME"));
	test_cmd("PWD", NULL, env);
	test_cmd("CD", "nonexistant_dir", env);
	test_cmd("CD", "minishell", env);
	ft_printf("---printvar (oldpwd, pwd)---\n");
	printvar(getvar(env, "OLDPWD"));
	printvar(getvar(env, "PWD"));
	exit(0);
}
