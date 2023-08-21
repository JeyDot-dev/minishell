/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:51:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/08/21 21:20:57 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) envp;
	t_env	*env;

	env = NULL;
	ft_export(&env, "POPI=lolilol");
	ft_env(env);
	ft_pwd();
	ft_cd(av, env);
	ft_pwd();
	exit(0);
	return (0);
}
