/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:41:49 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/10 15:54:09 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
int mini_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == '_')
		return (1);
	else
		return (0);
}
int check_export_arg(char *arg)
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
int add_to_env(char ***env, char *new_var)
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
		free_env(*env);
	*env = new_env;
	return (0);
}
int update_env(char ***env, char *new_var)
{
	char **tmp;

	tmp = calloc(2, sizeof(char *));
	if (!tmp)
		return (1);
	tmp[0] = extract_var_name(new_var);
	if (!tmp[0])
	{
		free(tmp);
		return (1);
	}
	tmp[1] = NULL;
	ft_unset(env, tmp);
	free(tmp[0]);
	free(tmp);
	add_to_env(env, new_var);
	return (0);
}
int	ft_export(char ***env, char **args)
{
	int	i;

	i = -1;
	if (!args  || !*args)
		ft_env(*env);
	while (args[++i])
	{
		if (check_export_arg(*args) > 0)
		{
			if (!getvar(*env, *args))
				add_to_env(env, *args);
			else
				update_env(env, *args);
		}
	}
	return (0);
}
