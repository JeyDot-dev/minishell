/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:15:48 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/17 13:15:49 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cmd(char **args, char ***env)
{
	if (!ft_strncmp(*args, "pwd", 4))
		return (ft_pwd());
	else if (!ft_strncmp(*args, "cd", 3))
		return (ft_cd(env, args + 1));
	else if (!ft_strncmp(*args, "env", 4))
		return (ft_env(*env));
	else if (!ft_strncmp(*args, "export", 7))
		return (ft_export(env, args + 1));
	else if (!ft_strncmp(*args, "unset", 6))
		return (ft_unset(env, args + 1));
	else if (!ft_strncmp(*args, "echo", 5))
		return (ft_echo(args));
	else if (!ft_strncmp(*args, "exit", 5))
		exit(0);
	return (777);
}