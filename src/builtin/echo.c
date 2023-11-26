/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:48:29 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 16:05:21 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (count_strings(args) > 1)
	{
		if (!ft_strncmp(args[1], "-n", 3))
		{
			n = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && *args[i])
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		write (1, "\n", 1);
	return (0);
}
