/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:58:26 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/24 21:29:03 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		special_builtins(t_cmds *cmds, t_shell *shell)
{
	if (!ft_strncmp(cmds->args[0], "exit", 5) && cmds->next == NULL)
		ft_exit(cmds, shell);
	if (!ft_strncmp(cmds->args[0], "cd", 3) && cmds->next == NULL)
		return (ft_cd(&shell->env, cmds->args));
	if (!ft_strncmp(cmds->args[0], "export", 7) && cmds->next == NULL)
		return (ft_export(&shell->env, cmds->args));
	if (!ft_strncmp(cmds->args[0], "unset", 6) && cmds->next == NULL)
		return (ft_unset(&shell->env, cmds->args));
	return (g_status);
}

void	exec_child(t_cmds cmd, t_shell *shell)
{
	if (dup2(cmd.fd_in, STDIN_FILENO) == -1)
		fatal_error("dup2() failed.");
	if (dup2(cmd.fd_out, STDOUT_FILENO) == -1)
		fatal_error("dup2() failed.");
	if (cmd.is_builtin)
		exit(builtin_cmd(cmd.args, &shell->env));
	else if (execve(cmd.path_cmd, cmd.args, shell->env) == -1)
			exit(127);
	exit(0);
}

int	exit_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
	exit (g_status);
}
int	execute(t_shell *shell)
{
	t_cmds	*tmp;
	pid_t	child;

	tmp = shell->cmds;
	g_status = special_builtins(tmp, shell);
	child = fork();
	if (child < 0)
		fatal_error("fork() failed.");
	if (child == 0)
	{
		while (tmp)
		{
			child = fork();
			if (tmp->run == 1 && child == 0)
				exit(g_status);
			else if (!child)
				exec_child(*tmp, shell);
			//close_fds(tmp->fd_out, tmp->fd_in);
			close_fds(tmp->fd_out, 0);
			tmp = tmp->next;
		}
		wait(&g_status);
//		waitpid(child, &g_status, 0);
		exit_status(g_status);
	}
	wait(&g_status);
	return (g_status);
}
