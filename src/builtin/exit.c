/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:10:38 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/20 19:19:29 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmds *cmds, t_shell *shell)
{
	long long int	nb;

	nb = 0;
	if (cmds->args[1] && cmds->args[2])
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		return (2);
	}
	else if (cmds->args[1])
	{
		nb = ft_atoi2(cmds->args[1]);
		if (nb == 2147483648)
		{
			ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", cmds->args[1]);
			free_shell(shell);
			exit(2);
		}
	}
	free_shell(shell);
	exit(nb);
}
