/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:15:48 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 17:33:45 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_builtins(t_cmds *cmds, t_shell *shell)
{
	if (cmds->run == 1)
		return (1);
	if (!ft_strncmp(cmds->args[0], "exit", 5) && cmds->next == NULL)
		ft_exit(cmds, shell);
	if (!ft_strncmp(cmds->args[0], "cd", 3) && cmds->next == NULL)
		return (ft_cd(&shell->env, cmds->args));
	if (!ft_strncmp(cmds->args[0], "export", 7) && cmds->next == NULL)
		return (ft_export(&shell->env, cmds->args));
	if (!ft_strncmp(cmds->args[0], "unset", 6) && cmds->next == NULL)
		return (ft_unset(&shell->env, cmds->args));
	return (127);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	builtin_cmd(char **args, char ***env)
{
	if (!ft_strncmp(*args, "pwd", 4))
		exit (ft_pwd());
	else if (!ft_strncmp(*args, "cd", 3))
		exit (ft_cd(env, args));
	else if (!ft_strncmp(*args, "env", 4))
		exit (ft_env(*env));
	else if (!ft_strncmp(*args, "export", 7))
		exit (ft_export(env, args));
	else if (!ft_strncmp(*args, "unset", 6))
		exit (ft_unset(env, args));
	else if (!ft_strncmp(*args, "echo", 5))
		exit (ft_echo(args));
	else if (!ft_strncmp(*args, "exit", 5))
		exit(0);
	exit (777);
}
