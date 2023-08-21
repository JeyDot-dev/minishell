/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:35:12 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/21 21:17:08 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_env	*new_variable(char	*var, char *data)
{
	t_env	*new_var;

	new_var = NULL;
	if (var && data)
	{
		new_var = malloc(sizeof(*new_var));
		if (!new_var)
			return (NULL);
		new_var->var = ft_strdup(var);
		new_var->data = ft_strdup(data);
	}
	return (new_var);
}
