/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:10:48 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 19:20:13 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	add_to_matrix(char ***env, char *new_var)
{
	char	**new_env;
	int		nb_strings;
	int		i;

	i = 0;
	nb_strings = count_strings(*env);
	if (!new_var)
		return (-1);
	new_env = ft_calloc(sizeof(char *), nb_strings + 2);
	if (!new_env)
		return (-1);
	new_env[nb_strings + 1] = NULL;
	while (*env && (*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	if (*env)
		free_matrix(*env);
	*env = new_env;
	return (0);
}
