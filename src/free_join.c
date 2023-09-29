/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:47:34 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/29 17:47:46 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*free_join(char *str, char *buffer)
{
	char	*new;

	if (str)
		new = ft_strjoin(str, buffer);
	else
		return (buffer);
	if (!new)
		return (NULL);
	str = ft_memdel(str);
	buffer = ft_memdel(buffer);
	return (new);
}
