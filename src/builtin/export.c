/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:41:49 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/25 09:48:20 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	mini_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == '_')
		return (1);
	else
		return (0);
}

int	check_export_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg || !mini_isalpha(*arg))
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("not a valid identifier\n", 2);
		return (-1);
	}
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i])
		return (i);
	else
		return (0);
}

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

	i = 0;
	if (!args[1])
		ft_env(*env);
	while (args[++i])
	{
		if (check_export_arg(args[i]) > 0)
		{
			if (!getvar(*env, args[i]))
				add_to_matrix(env, args[i]);
			else
				update_env(env, args[i]);
		}
	}
	return (0);
}
