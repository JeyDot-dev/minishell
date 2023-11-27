/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:10:38 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/27 02:10:32 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_byebye(void)
{
	char	*user;

	user = getenv("USER");
	if (user == NULL)
	{
		ft_fprintf(2, "(ﾉ◕ヮ◕)ﾉ"BLU"*"WHT":・ﾟ"
			YEL"✧"WHT" b y e b y e stranger"YEL"✧ "WHT"ﾟ・: "
			BLU"*"WHT"ヽ(◕ヮ◕ヽ)\n");
	}
	else
	{
		ft_fprintf(2, "(ﾉ◕ヮ◕)ﾉ"BLU"*"WHT":・ﾟ"
			YEL"✧"WHT" b y e b y e %s"YEL"✧ "WHT"ﾟ・: "
			BLU"*"WHT"ヽ(◕ヮ◕ヽ)\n", getenv("USER"));
	}
}

void	exit_shell(t_shell *shell, int n)
{
	free_shell(shell);
	exit(n);
}

void	ft_exit(t_cmds *cmds, t_shell *shell)
{
	long long int	nb;

	nb = 0;
	ft_byebye();
	if (!cmds || !cmds->args[1])
		exit_shell(shell, 0);
	if (ft_isdigit(cmds->args[1][0]) && cmds->args[2])
	{
		ft_fprintf(2, "minishell: exit: too many arguments\n");
		exit_shell(shell, 1);
	}
	else if (cmds->args[1])
	{
		nb = ft_atoi2(cmds->args[1]);
		if (nb == 2147483648)
		{
			ft_fprintf(2, "minishell: exit: %s: numeric argument required\n",
				cmds->args[1]);
			exit_shell(shell, 2);
		}
	}
	exit_shell(shell, nb);
}
