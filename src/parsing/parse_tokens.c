/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/20 14:08:42 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// if no cmd/arg found, t_status = 0, if no such file or dire, t_status = 1
/*
{
	int				pipes[2];
	int				fd_out;
	int				fd_in;
	int				run;
	char			**args;
	struct s_cmds	*next;
*/
t_cmds	*create_new_empty_cmd(void)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		fatal_error("malloc error while initiating cmd struct.");
	if (pipe(new->pipe))
		fatal_error("pipe() failed.");
	new->fd_out = 1;
	new->fd_in = 0;
	new->run = 0;
	new->is_builtin = 0;
	new->args = NULL;
	new->next = NULL;
	new->path_cmd = NULL;
	return (new);
}

t_cmds	*init_cmd_struct(int pipes)
{
	t_cmds	*new;
	t_cmds	*previous;
	t_cmds	*new_head;
	int		first;

	first = 1;
	while (pipes >= 0)
	{
		new = create_new_empty_cmd();
		if (first) 
			new_head = new;
		else
			previous->next = new;
		previous = new;
		first = 0;
		pipes--;
	}
	return(new_head);
}
int	replace_fd(int default_fd, int old_fd, int new_fd)
{
	//TODO: error if new_fd == -1 (open failed)
	if (old_fd != default_fd)
		close(old_fd);
	return (new_fd);
}
int	open_out(t_tokens *tokens, t_cmds **cmds)
{
	if (access(tokens->next->token, F_OK))
		open(tokens->next->token, O_CREAT, 0644);
	if (access(tokens->next->token, W_OK))
	{
		perror(tokens->next->token);
		g_status = errno;
	}
	else if (tokens->is_meta == CHR)
		(*cmds)->fd_out = replace_fd(1, (*cmds)->fd_out, open(tokens->next->token, O_WRONLY));
	else if (tokens->is_meta == CHRR)
		(*cmds)->fd_out = replace_fd(1, (*cmds)->fd_out, open(tokens->next->token, O_WRONLY | O_APPEND));
	return (0);
}
int	open_in(t_tokens *tokens, t_cmds **cmds)
{
	if (access(tokens->next->token, R_OK))
	{
		perror(tokens->next->token);
		g_status = errno;
	}
	else if (tokens->is_meta == CHL)
		(*cmds)->fd_in = replace_fd(0, (*cmds)->fd_in, open(tokens->next->token, O_RDONLY));
	else if (tokens->is_meta == CHLL)
		(*cmds)->fd_in = replace_fd(0, (*cmds)->fd_in, open(tokens->next->token, O_RDONLY));
	return (0);
}
void	open_in_out(t_tokens **tokens, t_cmds **cmds)
{
	//TODO: add HERE DOC
	if ((*cmds)->run == 1)
		return ;
	else if ((*tokens)->is_meta == CHR || (*tokens)->is_meta == CHRR)
		(*cmds)->run = open_out(*tokens, cmds);
	else if ((*tokens)->is_meta == CHL || (*tokens)->is_meta == CHLL)
		(*cmds)->run = open_in(*tokens, cmds);
	*tokens = (*tokens)->next->next;
}

void	set_cmd(t_tokens **tokens, char ***args)
{
	while (*tokens && !(*tokens)->is_meta)
	{
		add_to_matrix(args, (*tokens)->token);
		*tokens = (*tokens)->next;
	}
}
void	set_stdout_to_pipe(t_cmds *cmds)
{
	if (cmds->fd_out == 1 && cmds->next)
	{
		cmds->fd_out = cmds->next->pipe[1];
		cmds->next->fd_in = cmds->next->pipe[0];
	}
}
char	*try_paths(char *cmd, t_shell shell)
{
	char	*tmp[2];
	int		i;
	char	**path_split;

	i = 0;
	tmp[0] = NULL;
	tmp[1] = NULL;
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
		g_status = 127;
		cmds->run = 1;
	}
	return (0);
}
void	parsinator(t_cmds **cmds, t_tokens *tokens, t_shell *shell)
{
	t_cmds		*tmp_cmds;
	t_tokens	*tokens_tmp;

	tmp_cmds = *cmds;
	tokens_tmp = tokens;
	while (tmp_cmds)
	{
		if ((tokens_tmp && tokens_tmp->is_meta == PIPE) || (tmp_cmds && !tokens_tmp))
		{
			tmp_cmds->is_builtin = set_path_cmd(tmp_cmds, shell);
			ft_fprintf(2, "next cmd\n");
			set_stdout_to_pipe(tmp_cmds);
			tmp_cmds = tmp_cmds->next;
			if (tokens_tmp)
				tokens_tmp = tokens_tmp->next;
		}
		else if (tokens_tmp && tokens_tmp->is_meta)
			open_in_out(&tokens_tmp, &tmp_cmds);
		else if (tokens_tmp)
			set_cmd(&tokens_tmp, &(tmp_cmds)->args);
		else if (!tokens_tmp)
			tmp_cmds = NULL;
	}
}

int	parse_tokens(t_tokens *tokens, t_shell *shell)
{
	shell->cmds = init_cmd_struct(count_pipes(tokens));
	parsinator(&shell->cmds, tokens, shell);
	fprint_list_cmds(2, *shell, "parsed_tokens");
	//				find cmd and arguments if no cmd/arg > close fd and set error
	return (0);
}
