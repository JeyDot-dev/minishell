/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:41:49 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/09 19:58:37 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
int	check_export_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg || !ft_isalpha(*arg))
	{
		perror("not sure");
		return (-1);
	}
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i])
		return (i);
	else
		return (0);
}
char	*extract_var_name(char *str)
{
	int	i;
	char *var_name;

	i = 0;
	while (str && str[i] && str[i] != '=')
			i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (NULL);
	i = 0;
	while (str && str[i] && str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}
char	*extract_var_data(char *str)
{
	int	i;
	int	j;
	char	*var_data;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '=')
			i++;
	if (i == 0)
		return (NULL);
	if (str[i] == '=')
		i++;
	var_data = ft_calloc(sizeof(char), ft_strlen(&str[i]) + 1);
	if (!var_data)
		return (NULL);
	while (str[i])
		var_data[j++] = str[i++];
	return (var_data);
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
	while (*env && (*env)[i])
	{
		ft_printf("nb_string = %i | *env[%i] = %s\n", nb_strings, i, *env[i]);
		new_env[i] = ft_strdup(*env[i]);
		i++;
	}
	ft_printf("i = %i\n", i);
	new_env[i] = ft_strdup(new_var);
	ft_printf("new_env : %s, new_var : %s\n", *new_env, new_var);
	if (*env)
		free_env(*env);
				perror("add");
	*env = new_env;
	return (0);
}
int update_env(char ***env, char *new_var)
{
	char **tmp;

	tmp = calloc(2, sizeof(*tmp));
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
	if (!args)
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
