/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:18:03 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 19:20:43 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*extract_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (NULL);
	i = 0;
	while (str && str[i] && str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}
