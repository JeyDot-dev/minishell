/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:43:34 by gipaul            #+#    #+#             */
/*   Updated: 2023/08/21 11:33:15 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_size(char *env)
{
	size_t	i;
	
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_shell *shell, t_env *env)
{
	if (shell->env == env && env->next == NULL)
	{
		ft_memdel(shell->env->data);
		shell->env->data = NULL;
		shell->env->next = NULL;
		return;
	}
	ft_memdel(env->data);
	ft_memdel(env);
}

int	ft_unset(char **args, t_shell *shell)
{
	t_env *env;
	t_env *tmp;

	env = shell->env;
	if (!(args[1]))
		return (0);
	if (ft_strncmp(args[1], env->data, env_size(env->data)) == 0)
	{
		shell->env = (env->next) ? env->next : shell->env;
		free_node(shell, env);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_strncmp(args[1], env->next->data, env_size(env->next->data)) == 0)
		{
			tmp = env->next->next;
			free_node(shell, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return(0);
}	
