/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:13:25 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/30 16:31:34 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*prompt(void)
{
	char	pwd[PATH_MAX];
	char	*prompt;
	char	*tmp;
	char	*cmd_line;

	getcwd(pwd, sizeof(pwd));
	prompt = ft_strjoin("\e[0;36m", pwd);
	tmp = ft_strjoin("\e[0;35mminishell ", prompt);
	ft_memdel(prompt);
	if (g_status)
		prompt = ft_strjoin(tmp, "\e[0;31m $\e[0;37m ");
	else
		prompt = ft_strjoin(tmp, "\e[0;33m $\e[0;37m ");
	ft_memdel(tmp);
	cmd_line = readline(prompt);
	ft_memdel(prompt);
	return (cmd_line);
}
