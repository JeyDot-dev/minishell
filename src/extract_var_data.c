/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:30:45 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/10 17:07:04 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_data(char *str)
{
	int	i;
	int	j;
	char	*var_data;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '=')
			i++;
	if (i == 0)
		return (NULL);
	if (str[i] == '=')
		i++;
	var_data = ft_calloc(sizeof(char), ft_strlen(&str[i]) + 1);
	if (!var_data)
		return (NULL);
	while (str[i])
		var_data[j++] = str[i++];
	return (var_data);
}
