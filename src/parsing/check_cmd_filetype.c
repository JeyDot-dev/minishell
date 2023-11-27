/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_filetype.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:12:37 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/27 03:03:30 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*try_paths_extension(char *str, char *str2)
{
	if (str2 && access(str2, X_OK))
	{
		free(str2);
		return (ft_strdup(str));
	}
	return (str2);
}

char	*try_paths(char *cmd, t_shell shell)
{
	char	*tmp[2];
	int		i;
	char	**path_split;

	i = 0;
	tmp[0] = NULL;
	tmp[1] = NULL;
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	path_split = ft_split(getvar_data(shell.env, "PATH"), ':');
	while (path_split[i])
	{
		tmp[0] = ft_strjoin(path_split[i], "/");
		tmp[1] = ft_strjoin(tmp[0], cmd);
		if (!access(tmp[1], F_OK))
			break ;
		tmp[0] = ft_memdel(tmp[0]);
		tmp[1] = ft_memdel(tmp[1]);
		i++;
	}
	if (tmp[0])
		ft_memdel(tmp[0]);
	free_matrix(path_split);
	return (try_paths_extension(cmd, tmp[1]));
}

int	print_return(char *arg, int ret)
{
	if (ret == 1)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", arg);
		return (127);
	}
	else if (ret == 2)
	{
		ft_fprintf(2, "minishell: %s: is a directory\n", arg);
		return (126);
	}
	else if (ret == 3)
	{
		ft_fprintf(2, "minishell: %s: Permission denied\n", arg);
		return (126);
	}
	return (0);
}

char	*check_cmd_filetype(t_cmds *cmds, t_shell *shell)
{
	struct stat	stats;

	stat(cmds->args[0], &stats);
	cmds->path_cmd = try_paths(cmds->args[0], *shell);
	if (!access(cmds->path_cmd, X_OK) && S_ISDIR(stats.st_mode))
	{
		g_status = print_return(cmds->args[0], 2);
		cmds->run = 1;
	}
	if (!access(cmds->path_cmd, F_OK) && access(cmds->path_cmd, X_OK))
	{
		if (!S_ISREG(stats.st_mode))
			g_status = print_return(cmds->args[0], 3);
		else
			g_status = print_return(cmds->args[0], 1);
		cmds->run = 1;
	}
	else if (!cmds->path_cmd)
	{
		g_status = print_return(cmds->args[0], 1);
		cmds->run = 1;
	}
	return (cmds->path_cmd);
}
