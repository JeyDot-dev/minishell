/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:54:20 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 19:21:37 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	getvar_strncmp(char *s1, char *s2)
{
	char	*tmp;
	int		ret;

	tmp = ft_strjoin(s2, "=");
	if (!tmp)
		return (1);
	ret = ft_strncmp(s1, tmp, ft_strlen(tmp));
	free(tmp);
	return (ret);
}

int	getvar_index(char **env, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!env || !*var)
		return (-1);
	tmp = extract_var_name(var);
	if (!tmp || !*tmp)
		return (-1);
	while (env[i] && getvar_strncmp(env[i], var))
	{
		i++;
	}
	free(tmp);
	if (env[i])
		return (i);
	return (-1);
}

char	*getvar(char **env, char *var)
{
	char	*tmp;

	if (!env || !*var)
		return (NULL);
	tmp = extract_var_name(var);
	if (!tmp)
		return (NULL);
	while (*env && getvar_strncmp(*env, tmp))
	{
		env++;
	}
	free(tmp);
	return (*env);
}

char	*getvar_data(char **env, char *var)
{
	char	*tmp;

	tmp = getvar(env, var);
	if (!tmp)
		return (NULL);
	while (tmp && *tmp && *tmp != '=')
		tmp++;
	if (*tmp == '=')
		tmp++;
	return (tmp);
}
