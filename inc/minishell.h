/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:52:08 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/08 15:09:15 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
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
char	*extract_var_name(char *str);
char	*extract_var_data(char *str);
int	ft_find_var(t_env *env, char *var);
//------env_var list functions----
void	var_add_last(t_env **env, t_env *new_var);
t_env	*new_variable(char	*var, char *data);
t_env	*getvar(t_env *env, char *to_find);
void	printvar(t_env *env);
void	init_env(char **av, char **envp, t_env **env);
#endif
