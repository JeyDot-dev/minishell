/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:11:41 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 19:04:58 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int fd1, int fd2)
{
	int	fd[2];
	int	i;

	i = 0;
	fd[0] = fd1;
	fd[1] = fd2;
	while (i < 2)
	{
		if (fd[i] != STDIN_FILENO && fd[i] != STDOUT_FILENO)
		{
			close(fd[i]);
		}
		i++;
	}
}
