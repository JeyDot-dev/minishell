/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*          1                                         +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:54:44 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/27 01:01:58 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//if cd = 1 then too many args
//if cd = 2 then HOME not set
int	ft_count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	update_env_cd(char ***env, char *old_pwd)
{
	char	pwd[PATH_MAX];

	if (!getvar(*env, "PWD"))
		super_unset(env, "OLDPWD");
	else
	{
		super_double_export(env, "OLDPWD=", old_pwd);
		getcwd(pwd, sizeof(pwd));
		super_double_export(env, "PWD=", pwd);
	}
}

int	ft_cd(char ***env, char **args)
{
	char	*tmp;
	char	*old_pwd;

	if (args[1] && args[2])
	{
		ft_fprintf(2, "cd: too many arguments\n");
		return (1);
	}
	if (!args[1] || ((*args)[1] == '~' || (*args)[1] == 0))
		tmp = getvar_data(*env, "HOME");
	else
		tmp = args[1];
	if (!tmp)
		return (1);
	old_pwd = getvar_data(*env, "PWD");
	if (!chdir(tmp))
		update_env_cd(env, old_pwd);
	else
	{
		ft_fprintf(2, "cd: %s: %s\n", tmp, strerror(errno));
		return (1);
	}
	return (0);
}
