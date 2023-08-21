/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:06:47 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/21 21:16:07 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	var_add_last(t_env **env, t_env *new_var)
{
	if (env && !*env)
	{
		*env = new_var;
		return ;
	}
	while (env && (*env)->next)
		*env = (*env)->next;
	(*env)->next = new_var;
}
