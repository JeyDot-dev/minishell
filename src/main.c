/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:19:49 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/18 17:50:32 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)	ac;
	(void)	envp;
	pwd();
	cd(av[1]);
	ft_printf("\n");
//	for (char **env = envp; *env != 0; env++)
//	{
//		char *thisEnv = *env;
//		ft_printf("%s\n", thisEnv);
//}

	ft_printf("---GET ENV : %s---\n", getenv("HOME"));
	envp = malloc(1);
	envp[0] = ft_strdup("PATH=Wapiti");
	ft_printf("---print str : %s---\n", envp[0]);
	ft_printf("---GET ENV : %s---\n", getenv("PATH"));
	pwd();
	cd(av[2]);
	pwd();
	exit(0);
	return (0);
}
