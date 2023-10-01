/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:54:03 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/24 14:56:21 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	free_return_minone(char *to_free, char *to_write)
{
	ft_putendl_fd(to_write, 2);
	ft_memdel(to_free);
	return (-1);
}
void	*free_return_null(char *to_free, char *to_write)
{
	ft_putendl_fd(to_write, 2);
	return (ft_memdel(to_free));
}
