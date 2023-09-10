/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:29:02 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/10 15:54:12 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	super_export(char ***env, char *new_var)
{
	char *tmp[2];

	tmp[0] = new_var;
	tmp[1] = NULL;
	ft_export(env, tmp);
}
void	super_double_export(char ***env, char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	super_export(env, tmp);
	free(tmp);
}
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
void	init_env(char **av, char **envp, char ***env)
{
	char	*tmp;

	tmp = NULL;
	while (*envp)
	{
		super_export(env, *envp);
		envp++;
	}
	if (getvar(*env, "SHLVL") == NULL)
		super_export(env, "SHLVL=1");
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
