/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:52:08 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 11:31:40 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
typedef struct	s_cmds
{
	int				fd_out;
	int				fd_in;
	char			**args;
	struct s_cmds	*next;
}				t_cmds;

typedef struct	s_shell
{
	char	**env;
	char	*cmd_line;
	char	*last_cmd_line;
	char	**tokens;
	t_cmds	*cmds;
}				t_shell;
extern int g_status;
//-----------------MAIN FUNCTIONS---------------------------
char	*prompt(void);
void	update_history(t_shell *shell);
//-----------------BUILTIN FUNCTIONS---------------------------
//	v	executes builtin, returns 0 if it executed builtin, returns error code if builtin failed, returns... 777 if not a builtin.
int		builtin_cmd(char **args, char ***env);
int		ft_echo(char **args);
int		ft_env(char **env);
int		ft_pwd(void);
int		ft_cd(char ***env, char **args);
int		ft_export(char ***env, char **args);
int		ft_unset(char ***env, char **var);
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
//		v	makes an allocated copy of the data of a env variable (exemple input("VAR=data") = "data").
char	*extract_var_data(char *str);
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
//		v	function used to add a char* to a matrix.
int		add_to_matrix(char ***env, char *new_var);
//		v	function used to find and print an existing variable.
void	printvar(char **env, char *var);
//		v	prints a string in stderr and free another if needed, returns (void*)	NULL
void	*free_return_null(char *to_del, char *to_print);
//		v	prints a string in stderr and free another if needed, returns (int)		-1
int		free_return_minone(char *to_del, char *to_print);
//		v	join str and buffer and frees them
char	*free_join(char *str, char *buffer);
//		v	returns 1 if there are only spaces in the string else returns 0
int		only_spaces(char *str);
//--------------------PARSING FUNCTIONS-------------------------------
//		v	splits command line into usable tokens and expands variables
int		tokenizer(char	***split_cmd, char *cmd_line, char **env);
void	signal_handler(int sig);
#endif
