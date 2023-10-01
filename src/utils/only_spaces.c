/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 10:14:41 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 11:06:23 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_spaces(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == 32)
		i++;
	if (str[i] == 0)
		return (1);
	return (0);
}
