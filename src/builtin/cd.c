/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:54:44 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/21 11:24:15 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl(args[1], 2);
}

static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int	i;
	int	j;
	int	el_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->data, var, len) == 0)
		{
			el_alloc = ft_strlen(env->data) - len;
			if (!(oldpwd = malloc(sizeof(char) * el_alloc + 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->data[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->data[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (1);
	ft_memdel(oldpwd);
	return (0);
}

static int	go_to_path(int option, t_env *env)
{
	int	ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("HOME not set", STDERR);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("oldpwd not set", STDERR);
		if (!env_path)
			return (1);
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

int	ft_cd(char **args, t_env *env)
{
	int	cd_ret;

	if (!args[1])
		return (go_to_path(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);	
	}
	return (cd_ret);
}
