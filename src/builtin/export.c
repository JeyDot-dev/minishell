/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:41:49 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/27 02:42:48 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	update_env(char ***env, char *new_var)
{
	char	*tmp[3];

	tmp[1] = extract_var_name(new_var);
	if (!tmp[1])
		return (1);
	tmp[0] = "unset";
	tmp[2] = NULL;
	ft_unset(env, tmp);
	free(tmp[1]);
	add_to_matrix(env, new_var);
	return (0);
}

int	ft_export(char ***env, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!args[1])
		ft_env(*env);
	while (args[++i])
	{
		if (check_env_arg(args[i]) > 0)
		{
			if (!getvar(*env, args[i]))
				add_to_matrix(env, args[i]);
			else
				update_env(env, args[i]);
		}
		else
			j = 1;
	}
	return (j);
}
