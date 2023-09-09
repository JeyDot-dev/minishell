/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:00:28 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/09 19:42:20 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
void remove_from_env(char ***env, char *var)
{
	int	i[3];
	char **new_env;

	new_env = ft_calloc(sizeof(char *), count_strings(*env));
	i[0] = 0;
	i[1] = 0;
	i[2] = getvar_index(*env, var);
	if (!new_env)
		return ;
	while (*env[i[0]])
	{
		if (i[0] != i[2])
			new_env[i[1]++] = ft_strdup(*env[i[0]]);
		i[0]++;
	}
	free_env(*env);
	*env = new_env;
}
void	ft_unset(char ***env, char **var)
{
	while (*var)
	{
		if (getvar(*env, *var))
			remove_from_env(env, *var);
		*var += 1;
	}
}
