/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:41:49 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/21 21:20:29 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_find_var(t_env *env, char *var)
{
	int	i;

	i = 0;
	while (env && ft_strncmp(env->var, var, ft_strlen(var)))
	{
		env = env->next;
		i++;
	}
	if (env)
		return (i);
	return (-1);
}
char	*extract_var_name(char *str)
{
	int	i;
	char *var_name;

	i = 0;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (NULL);
	i = 0;
	while (str && str[i] && str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	if (str[i] == '=')
		var_name[i] = str[i];
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
int	free_export(char **args)
{
	free(args);
	return (-1);
}

int	ft_export(t_env **env, char *arg)
{
	char	**args;

	args = malloc(sizeof(args) * 2);
	args[0] = extract_var_name(arg);
	if (!args[0])
		free_export(args);
	args[1] = extract_var_data(arg);
	while (*env && ft_strncmp((*env)->var, args[0], ft_strlen(args[0])))
		*env = (*env)->next;
	if (*env)
	{
		free((*env)->var);
		free((*env)->data);
		(*env)->var = args[0];
		(*env)->data = args[1];
	}
	else
		var_add_last(env, new_variable(args[0], args[1]));
	return (0);
}
