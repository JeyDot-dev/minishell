/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:06:47 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/08 13:31:03 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	printvar(t_env *env)
{
	if (env)
		ft_printf("%s%s\n", env->var, env->data);
}
void	var_add_last(t_env **env, t_env *new_var)
{
	t_env	*tmp;
	
	tmp = *env;
	if (!tmp && new_var)
		*env = new_var;
	else if (env && new_var)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new_var;
	}
}
