/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:19:49 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/18 16:36:32 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)	ac;
	(void)	envp;
	for (char **env = envp; *env != 0; env++)
  	{
    	char *thisEnv = *env;
    	ft_printf("%s\n", thisEnv);
  	}
	pwd();
	cd(av[1]);
	pwd();
	exit(0);
	return (0);
}
