/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:58:26 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/21 15:14:30 by jsousa-a         ###   ########.fr       */
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
	close_fds(cmd.fd_out, cmd.fd_in);
	if (cmd.is_builtin)
	{
		exit(builtin_cmd(cmd.args, &shell->env));
	}
	else
		execve(cmd.path_cmd, cmd.args, shell->env);
	exit(127);
}

int	execute(t_shell *shell)
{
	t_cmds	*tmp;
	pid_t	child;

	tmp = shell->cmds;
	g_status = special_builtins(tmp, shell);
	ft_printf("pid: %d\n", getpid());
//	signal(SIGQUIT, SIG_DFL);
	child = fork();
	if (child < 0)
		fatal_error("fork() failed.");
	if (child == 0)
	{
		while (tmp)
		{
			child = fork();
			if (child < 0)
				fatal_error("fork() failed.");
			if (tmp->run == 1 && child == 0)
				exit(g_status);
			else if (!child)
				exec_child(*tmp, shell);
			close(tmp->pipe[1]);
			close(tmp->pipe[0]);
			close_fds(tmp->fd_out, tmp->fd_in);
			tmp = tmp->next;
		}
		waitpid(-1, &g_status, 0);
		exit(0);
	}
	waitpid(child, &g_status, 0);
	fprint_list_cmds(2, *shell, "post_execute");
	ft_fprintf(2, "POST EXECUTE\n");
	return (0);
}
