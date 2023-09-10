/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:52:08 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/10 19:00:41 by jsousa-a         ###   ########.fr       */
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
typedef struct	s_arg
{
	char			*cmd;
	char			**args;
	struct s_arg	*next;
}				t_arg;

typedef struct	s_shell
{
	char	**env;
}				t_shell;

//-----------------BUILTIN FUNCTIONS---------------------------
//	v	executes builtin, returns 0 if it executed builtin, returns error code if builtin failed, returns... 777 if not a builtin.
int	builtin_cmd(char **args, char ***env);
int	ft_echo(char **args);
int	ft_env(char **env);
int	ft_pwd(void);
int	ft_cd(char ***env, char **args);
int	ft_export(char ***env, char **args);
int	ft_unset(char ***env, char **var);
//-----------------ENV MANIPULATION FUNCTIONS-------------
//		v	function to unset with a char* instead of char**.
void	super_unset(char ***env, char *new_var);
//		v	function to export with a char* instead of char**.
void	super_export(char ***env, char *new_var);
//		v	function to export two str* concatanated (exemple s1="VAR=" s2="value").
void	super_double_export(char ***env, char *s1, char *s2);
//		v	initialize env in main.
void	init_env(char **av, char **envp, char ***env);
//		v	makes an allocated copy of the name of a env variable (exemple input("VAR=data") = "VAR=").
char	*extract_var_name(char *str);
//		v	function to return an existing env var as char * if doesn't exist returns NULL instead (exemple output: "VAR=data").
char	*getvar(char **env, char *var);
//		v	function to return an existing env var data as char * if doesn't exist returns NULL instead (exemple output: "data").
char	*getvar_data(char **env, char *var);
//		v	function that returns the index of an existing env var as int, if doesn't exist, returns -1 instead.
int		getvar_index(char **env, char *var);
//		v	function used to count the number of elements in a matrix (array[x][y]) returns 0 if empty.
int		count_strings(char **matrix);
//--------------------OTHER USEFUL FUNCTIONS---------------------------
//		v	function used to free a matrix (array[x][y]) and its content.
void	free_matrix(char **env);
//		v	function used to find and print an existing variable.
void	printvar(char **env, char *var);
#endif
