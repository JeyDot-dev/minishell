/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:52:08 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/21 21:12:41 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <errno.h>

typedef struct	s_env
{
	char	*var;
	char	*data;
	struct	s_env	*next;
}	t_env;

typedef struct	s_arg
{
	char			*cmd;
	char			**args;
	struct s_arg	*next;
}				t_arg;

typedef struct	s_shell
{
	t_env *env;
}				t_shell;

//-----Built-in functions-----
int	ft_echo(char **args);
int	ft_env(t_env *env);
int	ft_pwd(void);
int	exec_builtin(char **args, t_shell *shell);
int	is_builtin(char *command);
int	ft_cd(char **args, t_env *env);
int	ft_unset(char **a, t_shell *shell);
int	ft_export(t_env **env, char *arg);
//------env_var list functions----
void	var_add_last(t_env **env, t_env *new_var);
t_env	*new_variable(char	*var, char *data);
#endif
