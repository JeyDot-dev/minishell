/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:48:29 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/21 18:18:02 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* litteraly just a strlen for echo */
static int	nb_args(char **args)
{
	int	size;
	
	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if(nb_args(args) > 1)
	{
			while(args[i] && ft_strncmp(args[i], "-n", 2) == 0)
			{
				n = 1;
				i++;
			}
			while (args[i])
			{
				ft_putstr_fd(args[i], 1);	
				if (args[i + 1] && args[i][0] != '\0')
					write(1, " ", 1);
				i++;
			}
	}
	if (n = 0)
		write (1, "\n", 1);
	return (0);
}
