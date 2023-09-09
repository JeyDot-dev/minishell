/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:52:08 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/09 18:37:57 by jsousa-a         ###   ########.fr       */
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
int	ft_env(char **env);
int	ft_pwd(void);
int	exec_builtin(char **args, t_shell *shell);
int	is_builtin(char *command);
int	ft_cd(char **args, t_env *env);
int	ft_export(char ***env, char **args);
void	ft_unset(char ***env, char **var);
//------env manipulation functions----
char	*getvar(char **env, char *var);
int		getvar_index(char **env, char *var);
int		count_strings(char **matrix);
void	free_env(char **env);
void	printvar(char **env, char *var);
#endif
