/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprint_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:19:47 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 19:04:45 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	str_arr(int fd, char **strarr, char *str, int mode)
{
	if (mode == 2)
	{
		ft_fprintf(fd, "%s\tv\n", str);
		fprint_matrix(fd, strarr);
	}
	else if (strarr && *strarr)
		ft_fprintf(fd, "%s : %s\n", str, *strarr);
	else if (strarr)
		ft_fprintf(fd, "%s : no content\n", str);
	else
		ft_fprintf(fd, "%s : NULL\n", str);
}

void	fprint_struct_cmds(int fd, t_cmds cmds, int mode)
{
	if (mode == 0)
		return ;
	ft_fprintf(fd, RED"pipe[0] : %i\npipe[1] : %i\n",
		cmds.pipe[0], cmds.pipe[1]);
	ft_fprintf(fd, "fd_out : %i\n", cmds.fd_out);
	ft_fprintf(fd, "fd_in : %i\n", cmds.fd_in);
	ft_fprintf(fd, "run : %i\n", cmds.run);
	ft_fprintf(fd, "is_builtin : %i\n", cmds.is_builtin);
	str_arr(fd, cmds.args, "args", mode);
	if (cmds.next)
		ft_fprintf(fd, "next : %p\n"WHT, cmds.next);
	else
		ft_fprintf(fd, "next : NULL\n"WHT);
}

void	fprint_str(int fd, char *var, char *str)
{
	if (var)
		ft_fprintf(fd, "%s : %s\n", str, var);
	else
		ft_fprintf(fd, "%s : NULL\n", str);
}

void	fprint_list_cmds(int fd, t_shell shell, char *str)
{
	int		i;
	t_cmds	*tmp;

	if (shell.debug == 0)
		return ;
	tmp = shell.cmds;
	ft_fprintf(fd, RED"---DEBUG t_cmds list : %s---\n", str);
	i = 0;
	while (tmp)
	{
		ft_fprintf(fd, RED"--cmd %i\n", i);
		fprint_struct_cmds(fd, *tmp, shell.debug);
		tmp = tmp->next;
		i++;
	}
}

void	fprint_shell(int fd, t_shell *shell, char *str)
{
	if (shell->debug == 0)
		return ;
	ft_fprintf(2, RED"---- DEBUG t_shell : %s ----\n", str);
	if (shell->debug == 3)
	{
		shell->debug -= 1;
		str_arr(fd, shell->env, "env", shell->debug);
	}
	fprint_str(fd, shell->cmd_line, "cmd_line");
	fprint_str(fd, shell->last_cmd_line, "last_cmd_line");
	ft_fprintf(fd, "status code : %i\n", g_status);
	ft_fprintf(fd, "--tokens--\n");
	if (shell->tokens)
		print_tokens(shell->tokens);
	else
		ft_fprintf(fd, "NULL\n"WHT);
	ft_fprintf(fd, WHT"\n");
}
