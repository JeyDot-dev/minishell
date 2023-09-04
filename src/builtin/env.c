/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:52:01 by gipaul            #+#    #+#             */
/*   Updated: 2023/08/21 18:53:25 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->data, 1);
		env = env->next;
	}	
	if (env)
		ft_putendl_fd(env->data, 1);
	return (0);
}
