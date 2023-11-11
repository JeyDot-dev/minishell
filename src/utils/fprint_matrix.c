/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:55:57 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/11 16:01:08 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	fprint_matrix(int fd, char **matrix)
{
	if (!matrix)
		ft_putstr_fd("NULL\n", fd);
	while (matrix && *matrix)
	{
		ft_fprintf(fd, "\t|\"%s\"\n", *matrix);
//		ft_putstr_fd(*matrix, fd);
		matrix++;
	}
}
