/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:16:01 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/24 14:21:10 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*scpy;
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	if (len < n)
		scpy = (char *) ft_calloc(sizeof(*str) * (len + 1), 1);
	else
		scpy = (char *) ft_calloc(sizeof(*str) * (n + 1), 1);
	if (!scpy)
		return (scpy);
	while (str[i] && i < n)
	{
		scpy[i] = str[i];
		i++;
	}
	return (scpy);
}
