/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:18:53 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 18:44:32 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	not_eof(int hd_pipe[2], char *delimiter)
{
	ft_fprintf(2, "\n         warning: here-doc delimited by end-of-file(CTRL-D), \
wanted `%s'... but ok babyy let's go\n", delimiter);
	close(hd_pipe[1]);
	if (init_sigint(signal_handler, SIGINT))
		fatal_error("init_sigint() failed.");
	return (hd_pipe[0]);
}

void	write_to_pipe(int fd, char **user_input, t_shell *shell)
{
	*user_input = expand_string(*user_input, shell);
	write(fd, *user_input, ft_strlen(*user_input));
	write(fd, "\n", 1);
	*user_input = ft_memdel(*user_input);
}

int	here_doc(char *delimiter, t_shell *shell)
{
	int		hd_pipe[2];
	char	*user_input;

	if (pipe(hd_pipe))
		fatal_error("pipe() failed.");
	if (init_sigint(signal_troll, SIGINT))
		fatal_error("init_sigint() failed.");
	while (g_status != SIGINT)
	{
		user_input = readline(HDOC_PROMPT);
		if (!user_input)
			return (not_eof(hd_pipe, delimiter));
		if (!ft_strncmp(user_input, delimiter, ft_strlen(delimiter) + 1))
			break ;
		else if (user_input)
			write_to_pipe(hd_pipe[1], &user_input, shell);
	}
	if (init_sigint(signal_handler, SIGINT))
		fatal_error("init_sigint() failed.");
	close(hd_pipe[1]);
	if (user_input)
		ft_memdel(user_input);
	return (hd_pipe[0]);
}
