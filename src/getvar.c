/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:54:20 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/09 19:00:43 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int		getvar_strncmp(char *s1, char *s2)
{
	char *tmp;
	int	ret;

	tmp = ft_strjoin(s2, "=");
	if (!tmp)
		return (1);
	ret = ft_strncmp(s1, tmp, ft_strlen(tmp));
	free(tmp);
	return (ret);
}
int	getvar_index(char **env, char *var)
{
	int	i;

	if (!*env || !*var)
		return (-1);
	while (env[i] && getvar_strncmp(env[i], var))
		i++;
	return (i);
}
char	*getvar(char **env, char *var)
{
	if (!env || !*var)
		return (NULL);
	while (*env && getvar_strncmp(*env, var))
		env++;
	return (*env);
}
