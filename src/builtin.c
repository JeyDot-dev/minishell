/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <test42@student.42.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:17:39 by gipaul            #+#    #+#             */
/*   Updated: 2023/09/09 17:50:39 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "env", 3) == 0)
		return (1);
//	if (ft_strncmp(command, "export", 6) == 0)
//		return (1);
	if (ft_strncmp(command, "unset", 5) == 0)
		return (1);
	return (0);
}

/*int	exec_builtin(char **args, t_shell *shell)
{
	int	result;

	result = 0;
	if (ft_strncmp(args[0], "echo", 4) == 0)
		result = ft_echo(args);
	if (ft_strncmp(args[0], "cd", 2) == 0)
		result = ft_cd(args, shell->env);
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		result = ft_pwd();
	if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env(shell->env);
//	if (ft_strncmp(args[0], "export", 6) == 0)
//		ft_export();
	if (ft_strncmp(args[0], "unset", 5) == 0)
		ft_unset(args, shell);
	return (result);
}*/
