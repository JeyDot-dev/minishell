/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:52:08 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/21 18:14:21 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <errno.h>

typedef struct	s_env
{
	char	*data;
	struct	s_env	*next;
}	t_env;

typedef struct	s_shell
{
	t_env *env;
}	t_shell;

//-----Built-in functions-----
int	ft_echo(char **args);
int	ft_env(t_env *env);
int	ft_pwd(void);
int	exec_builtin(char **args, t_shell *shell);
int	is_builtin(char *command);
int	ft_cd(char **args, t_env *env);
int	ft_unset(char **a, t_shell *shell);

#endif
