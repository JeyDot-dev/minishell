/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:58:26 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/27 03:02:14 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_status = WTERMSIG(status) + 128;
		if (g_status == 129 || g_status == 126)
			g_status = 1;
	}
	return (g_status);
}

void	close_pipes(t_cmds *cmd)
{
	t_cmds	*tmp;

	tmp = cmd;
	if (tmp->next)
	{
		tmp = tmp->next;
		close(tmp->pipe[0]);
		tmp = tmp->next;
	}
	while (tmp)
	{
		close(tmp->pipe[1]);
		close(tmp->pipe[0]);
		tmp = tmp->next;
	}
}

void	exec_child(t_cmds cmd, t_shell *shell)
{
	if (cmd.next)
		close_pipes(&cmd);
	if (cmd.fd_in != STDIN_FILENO)
	{
		if (dup2(cmd.fd_in, STDIN_FILENO) == -1)
			fatal_error("dup2() failed.");
		close(cmd.pipe[0]);
		close(cmd.fd_in);
	}
	if (cmd.fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd.fd_out, STDOUT_FILENO) == -1)
			fatal_error("dup2() failed.");
		close(cmd.fd_out);
	}
	if (cmd.is_builtin)
		exit(builtin_cmd(cmd.args, &shell->env));
	else if (execve(cmd.path_cmd, cmd.args, shell->env) == -1)
	{
		exit(1);
	}
	exit(127);
}

int	execute(t_shell *shell)
{
	t_cmds	*tmp;
	pid_t	child;

	signal(SIGCHLD, handle_sigchild);
	tmp = shell->cmds;
	if (is_builtin(tmp->args[0]) && !tmp->next)
	{
		g_status = special_builtins(tmp, shell);
		return (g_status);
	}
	while (tmp)
	{
		child = fork();
		if (tmp->run == 1 && child == 0)
			exit(g_status);
		else if (!child)
			exec_child(*tmp, shell);
		close(tmp->pipe[1]);
		close(tmp->pipe[0]);
		close_fds(tmp->fd_out, tmp->fd_in);
		tmp = tmp->next;
	}
	if (child)
		waitpid(child, &g_status, 0);
	return (exit_status(g_status));
}
