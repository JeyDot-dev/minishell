/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:58:26 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 15:16:09 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
	return (g_status);
}

void	handle_sigchild(int sig)
{
	(void)sig;
	while (waitpid(-1, &g_status, 0) > 0)
	{
		g_status = exit_status(g_status);
	//	ft_fprintf(2,"THE CHILD HAS DIED!!! g_status: %d\n", g_status);
	//	if (WIFEXITED(g_status))
		//	g_status = WEXITSTATUS(g_status);
		//else if (WIFSIGNALED(g_status))
	//		g_status = WTERMSIG(g_status) + 128;
	}
}
int		special_builtins(t_cmds *cmds, t_shell *shell)
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
	if (!ft_strncmp(cmds->args[0], "env", 4) && cmds->next == NULL)
		return (ft_env(shell->env));
	if (!ft_strncmp(cmds->args[0], "echo", 5) && cmds->next == NULL)
		return (ft_echo(cmds->args));
	if (!ft_strncmp(cmds->args[0], "pwd", 4) && cmds->next == NULL)
		return (ft_pwd());
	return (127);
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
	ft_fprintf(2, "child: %d\n", getpid());
	if (cmd.next)
		close_pipes(&cmd);
	//if (cmd.next)
	//	close(cmd.next->pipe[0]);
	if (cmd.fd_in != STDIN_FILENO)
	{
		if (dup2(cmd.fd_in, STDIN_FILENO) == -1)
			fatal_error("dup2() failed.");
		close(cmd.pipe[0]);
		close(cmd.fd_in);
	}
//	if (cmd.fd_in != STDIN_FILENO)
//		close(cmd.fd_in);
	if (cmd.fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd.fd_out, STDOUT_FILENO) == -1)
			fatal_error("dup2() failed.");
		close(cmd.fd_out);
	}
	if (cmd.is_builtin)
		exit(builtin_cmd(cmd.args, &shell->env));
	else if (execve(cmd.path_cmd, cmd.args, shell->env) == -1)
			exit(127);
	exit(0);
}

int	execute(t_shell *shell)
{
	t_cmds	*tmp;
	pid_t	child;
	//int	i;
//	struct stat *fstat_struct;

//	i = 0;
	signal(SIGCHLD, handle_sigchild);
	tmp = shell->cmds;
	g_status = special_builtins(tmp, shell);
	if (g_status != 127)
		tmp = tmp->next;
/*	child = fork();
//	while (1);
	if (child < 0)
		fatal_error("fork() failed.");
	if (child == 0)
	{*/
		while (tmp)
		{
			//fstat_struct = NULL;
			child = fork();
//			if (child)
//				ft_fprintf(2,"child postfork: %d\n", child);
			if (tmp->run == 1 && child == 0)
				exit(1);
			else if (!child)
				exec_child(*tmp, shell);
			close(tmp->pipe[1]);
			close(tmp->pipe[0]);
			close_fds(tmp->fd_out, tmp->fd_in);
//			fstat(tmp->fd_out, fstat_struct);
//			if(S_ISFIFO(fstat_struct->st_mode))
//				close(tmp->next->pipe[1]);
//			close_fds(tmp->fd_out, tmp->fd_in);
//			if (tmp->next)
//				close(tmp->next->fd_in);
//			close_fds(tmp->fd_out, tmp->fd_in);
			tmp = tmp->next;
		}
//	waitpid(child, &g_status, 0);
/*		waitpid(-1, &g_status, 0);
//		wait(&g_status);
//		waitpid(child, &g_status, 0);
		exit_status(g_status);
	}*/
	if (child)
		waitpid(child, &g_status, 0);
//	while (i < 100000000)
//		i++;
	//wait(&g_status);
	return (exit_status(g_status));
}
