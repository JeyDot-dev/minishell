/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:52:08 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/11 14:41:58 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# define CHL	1
# define CHLL	2
# define CHR	3
# define CHRR	4
# define PIPE	5
// ^  [< = 1] [<< = 2] [> = 3] [>> = 4] [| = 5]
extern int	g_status;
typedef struct s_cmds
{
	int				pipe[2];
	int				fd_out;
	int				fd_in;
	int				run;
	char			**args;
	struct s_cmds	*next;
}				t_cmds;
typedef struct s_tokens
{
	char			*token;
	int				is_meta;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_shell
{
	char		**env;
	char		*cmd_line;
	char		*last_cmd_line;
	t_tokens	*tokens;
	t_cmds		*cmds;
	int			debug;
}				t_shell;
typedef struct s_io
{
	char	*in;
	char	*out;
	int		prev_pipe;
}				t_io;
//-----------------MAIN FUNCTIONS---------------------------
char	*prompt(void);
void	update_history(t_shell *shell);
//		v	splits command line into usable tokens and expands variables
int		tokenizer(t_tokens **tokens, t_shell *shell);
//			--tokenizer_utilities--
//		v	check the validity of the meta character by checking what's after it
int		check_post_meta(t_tokens *tokens, char *cmd_line, int i, char sign);
//		v	check if character is "|><" returns 0 if not
int		is_meta(const int c);
//		v	check if character is potential string (c != 32 || is_meta(c) || \0)
int		is_string(const int c);
//		v	expand all variables in string (and creates a new one expanded)
char	*expand_string(char *str, char **env);
//		 __|finds end of string and returns index
//		v  |checks for quotes and output error if needed
int		find_end_of_token(char *cmd_line, int i, int mode);
int		add_token(char *new_token, int is_meta, t_tokens **token_list);
//-----------------BUILTIN FUNCTIONS---------------------------
//		 __|executes builtin, returns 0 if it executed builtin
//		v  |returns error code if builtin failed, returns 777 if not a builtin.
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
//		 __|function to export two str* concatenated
//		v  |(exemple s1="VAR=" s2="value").
void	super_double_export(char ***env, char *s1, char *s2);
//		v	initialize env in main.
void	init_env(char **av, char **envp, char ***env);
//		 __|makes an allocated copy of the name of a env variable
//		v  |(exemple input("VAR=data") = "VAR=").
char	*extract_var_name(char *str);
//		 __|makes an allocated copy of the data of a env variable
//		v  |(exemple input("VAR=data") = "data").
char	*extract_var_data(char *str);
//		 __|function to return an existing env var as char *.
//		v  |if doesn't exist returns NULL instead (exemple output: "VAR=data").
char	*getvar(char **env, char *var);
//		 __|function to return an existing env var data as char *.
//		v  |if doesn't exist returns NULL instead (exemple output: "data").
char	*getvar_data(char **env, char *var);
//		 __|function that returns the index of an existing env var as int.
//		v  |if doesn't exist, returns -1 instead.
int		getvar_index(char **env, char *var);
//		 __|function used to count the number of elements in a matrix
//		v  |returns 0 if empty.
int		count_strings(char **matrix);
//--------------------OTHER USEFUL FUNCTIONS---------------------------
//		v	function used to free a matrix and its content.
void	free_matrix(char **env);
//		v	frees the struct s_token
void	delete_tokens(t_tokens *tokens_struct);
//		v	function used to add a char* to a matrix.
int		add_to_matrix(char ***env, char *new_var);
//		v	function used to find and print an existing variable.
void	printvar(char **env, char *var);
//		 __|prints a string in stderr and free another if needed.
//		v  |returns (void*) NULL
void	*free_return_null(char *to_del, char *to_print);
//		 __|prints a string in stderr and free another if needed.
//		v  |returns (int) -1
int		free_return_minone(char *to_del, char *to_print);
//		v	join str and buffer and frees them
char	*free_join(char *str, char *buffer);
//		v	returns 1 if there are only spaces in the string else returns 0
int		only_spaces(char *str);
void	fprint_matrix(int fd, char **matrix);
void	fatal_error(char *to_print);
//--------------------DEBUG FUNCTIONS---------------------------------
//		 __|debug function to print a single t_cmds struct
//		v  |(has different modes depending on debug mode)
void	fprint_struct_cmds(int fd, t_cmds cmds, int mode);
//		 __|debug function to print the entirety of t_cmds list
//		v  |(has different modes depending on debug mode (shell.debug))
void	fprint_list_cmds(int fd, t_shell shell, char *str);
//		 __|debug function to print t_shell.
//		v  |(has different modes depending on debug mode (shell->debug))
void	fprint_shell(int fd, t_shell *shell, char *str);
void	print_tokens(t_tokens *tokens);
//--------------------PARSING FUNCTIONS-------------------------------
//		v	function used to parse the tokens into a list of commands.
int		parse_tokens(t_tokens *tokens, t_shell *shell);
int		count_pipes(t_tokens *tokens);
void	close_pipe(t_cmds *cmd);
void	signal_handler(int sig);
#endif
