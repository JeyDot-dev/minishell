/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:51:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/08/22 21:08:20 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env2(t_env *env)
{
	ft_printf("IN ENV2\n");
	while (env)
	{
		ft_printf("ENV2 : %s%s\n", env->var, env->data);
		env = env->next;
	}
}
int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) envp;
	t_env	*env;

	env = NULL;
	init_env(av, envp, &env);
	ft_printf("-----env2----\n");
	ft_env2(env);
	ft_export(&env, "MALI=Triko");
	ft_export(&env, "POPI=lolilol");
	ft_export(&env, "POPI=Pakolama");
	ft_printf("-----printvar----\n");
	printvar(getvar(env, "POPI"));
	ft_pwd();
	ft_cd(av, env);
	ft_pwd();
	exit(0);
	return (0);
}
