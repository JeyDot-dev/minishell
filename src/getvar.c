/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:20:30 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/22 18:20:32 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*getvar(t_env *env, char *to_find)
{
	while (env)
	{
		if (ft_strncmp(env->var, to_find, ft_strlen(to_find)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
