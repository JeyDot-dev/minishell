/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:29:02 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 18:19:18 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	export_underscore_var(char ***env, char *av)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("_", getvar(*env, "PWD") + 3);
	if (!tmp)
		return ;
	tmp2 = ft_strjoin(tmp, "/");
	free(tmp);
	if (!tmp2)
		return ;
	tmp = ft_strjoin(tmp2, av);
	free(tmp2);
	if (!tmp)
		return ;
	super_export(env, tmp);
	free(tmp);
}

void	update_shlvl(char *shlvl, char ***env)
{
	int		new_lvl;
	char	*itoa;

	new_lvl = ft_atoi(shlvl) + 1;
	itoa = ft_itoa(new_lvl);
	super_double_export(env, "SHLVL=", itoa);
	free(itoa);
}

void	init_env(char **av, char **envp, char ***env)
{
	char	*tmp;

	tmp = NULL;
	*env = NULL;
	while (*envp)
	{
		super_export(env, *envp);
		envp++;
	}
	if (getvar(*env, "SHLVL") == NULL)
		super_export(env, "SHLVL=1");
	else
		update_shlvl(getvar_data(*env, "SHLVL"), env);
	if (getvar(*env, "PWD") == NULL)
	{
		tmp = getcwd(tmp, PATH_MAX + 1);
		super_double_export(env, "PWD=", tmp);
		free(tmp);
	}
	if (getvar(*env, "_") == NULL)
		export_underscore_var(env, *av);
	if (getvar(*env, "PATH") == NULL)
		super_export(env, "PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/bin");
	super_export(env, "SUPER_SECRET_VAR=YouWishYouKnew");
}
