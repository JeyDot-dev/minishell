/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:03:03 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/22 21:02:06 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
char	*concat(char *str, char *str_two)
{
	int	i;
	int	j;
	int	len;
	char	*result;

	len = 0;
	i = 0;
	j = 0;
	while (*str++)
		len++;
	while (*str_two++)
		len++;
	result = ft_calloc(len + 1, 1);
	if (!result)
		return (NULL);
	while (str[i])
		result[j++] = str[i++];
	i = 0;
	while (str_two[i])
		result[j++] = str_two[i++];
	return (result);
}
void	init_env(char **av, char **envp, t_env **env)
{
	char	*tmp;
//	char	*tmp2;

	tmp = NULL;
	while (*envp)
	{
		ft_export(env, *envp);
		envp++;
	}
	if (getvar(*env, "SHLVL") == NULL)
		var_add_last(env, new_variable("SHLVL=", "1"));
	if (getvar(*env, "PWD") == NULL)
	{
		tmp = getcwd(tmp, PATH_MAX + 1);
		var_add_last(env, new_variable("PWD=", tmp));
		free(tmp);
	}
	if (getvar(*env, "_") == NULL)
	{
		var_add_last(env, new_variable("_=", av[0]));
	}
	if (getvar(*env, "PATH") == NULL)
		ft_export(env, "PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin");
}
