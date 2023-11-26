/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 18:55:59 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*try_paths(char *cmd, t_shell shell)
{
	char	*tmp[2];
	int		i;
	char	**path_split;

	i = 0;
	tmp[0] = NULL;
	tmp[1] = NULL;
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	path_split = ft_split(getvar_data(shell.env, "PATH"), ':');
	while (path_split[i])
	{
		tmp[0] = ft_strjoin(path_split[i], "/");
		tmp[1] = ft_strjoin(tmp[0], cmd);
		if (!access(tmp[1], X_OK))
			break ;
		tmp[0] = ft_memdel(tmp[0]);
		tmp[1] = ft_memdel(tmp[1]);
		i++;
	}
	if (tmp[0])
		ft_memdel(tmp[0]);
	free_matrix(path_split);
	return (tmp[1]);
}

int	set_path_cmd(t_cmds *cmds, t_shell *shell)
{
	if (!cmds->args)
	{
		cmds->run = 1;
		return (0);
	}
	if (is_builtin(cmds->args[0]))
		return (1);
	cmds->path_cmd = try_paths(cmds->args[0], *shell);
	if (!cmds->path_cmd || access(cmds->path_cmd, X_OK))
	{
		ft_fprintf(2, "minishell: %s: command not found\n", cmds->args[0]);
		g_status = 1;
		cmds->run = 1;
	}
	return (0);
}

void	set_cmd(t_tokens **tokens, t_cmds *cmds, t_shell *shell)
{
	char	***args;

	args = &cmds->args;
	while (*tokens && !(*tokens)->is_meta)
	{
		add_to_matrix(args, (*tokens)->token);
		*tokens = (*tokens)->next;
	}
	if (!cmds->path_cmd)
		cmds->is_builtin = set_path_cmd(cmds, shell);
}

void	parsinator(t_cmds **cmds, t_tokens *tokens, t_shell *shell)
{
	t_cmds		*tmp_cmds;
	t_tokens	*tokens_tmp;

	tmp_cmds = *cmds;
	tokens_tmp = tokens;
	while (g_status != SIGINT && tmp_cmds)
	{
		if ((tokens_tmp && tokens_tmp->is_meta == PIPE) || (
				tmp_cmds && !tokens_tmp))
		{
			set_fd_to_pipe(tmp_cmds);
			tmp_cmds = tmp_cmds->next;
			if (tokens_tmp)
				tokens_tmp = tokens_tmp->next;
		}
		else if (!tokens_tmp)
			tmp_cmds = NULL;
		else if (tmp_cmds->run)
			tokens_tmp = tokens_tmp->next;
		else if (tokens_tmp->is_meta)
			open_io(&tokens_tmp, &tmp_cmds, shell);
		else
			set_cmd(&tokens_tmp, tmp_cmds, shell);
	}
}

int	parse_tokens(t_tokens *tokens, t_shell *shell)
{
	shell->cmds = init_cmd_struct(count_pipes(tokens));
	parsinator(&shell->cmds, tokens, shell);
	if (g_status == SIGINT)
	{
		fprint_list_cmds(2, *shell, "parsed_tokens");
		free_cmds(shell->cmds);
		shell->cmds = NULL;
	}
	else
		fprint_list_cmds(2, *shell, "parsed_tokens");
	return (0);
}
