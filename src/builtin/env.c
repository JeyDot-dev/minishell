/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:52:01 by gipaul            #+#    #+#             */
/*   Updated: 2023/08/18 10:54:58 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl(env->data);
		env = env->next;
	}	
	if (env)
		ft_putendl(env->data);
	return (0);
}
