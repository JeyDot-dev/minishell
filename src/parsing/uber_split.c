/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uber_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:00:22 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/30 11:46:57 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
int		is_meta(const int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}


int		is_string(const int c)
{
	if (c == 0 || is_meta(c) || c == 32)
		return (0);
	return (1);
}

int		find_end_of_token(char *cmd_line, int i, int mode)
{
	while (mode == 1 && cmd_line[i] && cmd_line[i] != '\"')
		i++;
	while (mode == 2 && cmd_line[i] && cmd_line[i] != '\'')
		i++;
	if (mode && !cmd_line[i])
		return (free_return_minone(NULL, "No closing quotes"));
	while (mode == 0 && is_string(cmd_line[i]) &&
			cmd_line[i] != '\'' && cmd_line[i] != '\"')
		i++;
	return (i);
}

int	expand_var(char *str, char **var, int i, char **env)
{
	int		start;
	char	*buffer;
	char	*new_var;
	
	while (str[i] && str[i] == '$')
		i++;
	start = i;
	if (!str[i])
		*var = ft_strdup("$");
	else if (str[i] == '?')
		*var = ft_itoa(g_status);
	if (str[i] == '?')
		i++;
	else
	{
		while (str[i] && str[i] != '$' && !is_meta(str[i]) &&
				str[i] != '\'' && str[i] != '\"' && str[i] != 32)
			i++;
		buffer = ft_strndup(&str[start], i - start + 1);
		new_var = extract_var_data(getvar(env, buffer));
		ft_memdel(buffer);
		if (new_var)
			*var = ft_strdup(new_var);
		ft_memdel(new_var);
	}
	return (i);
}

char	*expand_string(char *str, char **env)
{
	char	*new_s;
	char	*var;
	int		start;
	int		end;

	new_s = NULL;
	var = NULL;
	start = 0;
	end = 0;
	while (str[start])
	{
		if (str[start] == '$')
		{
			start = expand_var(str, &var, end, env);
			end = start;
			new_s = free_join(new_s, var);
		}
		while (str[end] && str[end] != '$')
			end++;
		new_s = free_join(new_s, ft_strndup(&str[start], end - start));
		start = end;
	}
	return (new_s);
}

int		get_string(char *cmd_line, char **buffer, int i, char **env)
{
	int	start[2];

	start[0] = i;
	start[1] = 0;
			
	if (cmd_line[i] == '\"' || cmd_line[i] == '\'')
	{
		start[1] = 1;
		if (cmd_line[i] == '\'')
			start[1] = 2;
		start[0] = ++i;
	}
	else
		start[1] = 0;
	i = find_end_of_token(cmd_line, i, start[1]);
	if (i < 0)
		return (i);
	*buffer = ft_strndup(&cmd_line[start[0]], i - start[0]);
	if (start[1] == 0 || start[1] == 1)
		*buffer = expand_string(*buffer, env);
	if (start[1])
		i++;
	return (i);
}

int		str_token(char ***splitted_cmd, char *cmd_line, int i, char **env)
{
	char	*new_str;
	char	*buffer;

	buffer = NULL;
	new_str = NULL;
	while (is_string(cmd_line[i]))
	{
		i = get_string(cmd_line, &buffer, i, env);
		if (i >= 0)
			new_str = free_join(new_str, buffer);
	}
	if (new_str && add_to_matrix(splitted_cmd, new_str) != 0)
		i = -1;
	ft_memdel(new_str);
	return (i);
}
int		check_post_meta_long(char *cmd_line, int i, char sign)
{
	int	ret;

	ret = 42;
	if (cmd_line[i] == sign)
	{
		ret = sign % 60 + 1;
		i++;
	}
	while (cmd_line[i] && cmd_line[i] == 32)
		i++;
	if (cmd_line[i] && !is_meta(cmd_line[i]))
	{
		if (ret != 42)
			return (ret);
		return (sign % 60);
	}
	return (42);
}
int		check_post_meta(char *cmd_line, int i, char sign)
{
	int	ret;

	i++;
	ret = 42;
	if (sign == '|')
	{
		while (cmd_line[i] && cmd_line[i] == 32)
			i++;
		if (cmd_line[i] && cmd_line[i] != '|')
			return(sign % 60);
	}
	else if (sign == '<' || sign == '>')
		ret = check_post_meta_long(cmd_line, i, sign);
	return (ret);
}
int		meta_token(char ***splitted_cmd, char *cmd_line, int i)
{
	int	j;

	j = check_post_meta(cmd_line, i, cmd_line[i]);
	if (j == 42)
	{
		ft_putstr_fd("Error near ", 2);
		ft_putchar_fd(cmd_line[i], 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	i++;
	if (j == 0)
		add_to_matrix(splitted_cmd, "<");
	if (j == 1)
		add_to_matrix(splitted_cmd, "<<");
	if (j == 2)
		add_to_matrix(splitted_cmd, ">");
	if (j == 3)
		add_to_matrix(splitted_cmd, ">>");
	if (j == 4)
		add_to_matrix(splitted_cmd, "|");
	if (j == 3 || j == 1)
		i++;
	return (i);

}

int		create_token(char ***splitted_cmd, char *cmd_line, int i, char **env)
{
	if (is_meta(cmd_line[i]))
		i = meta_token(splitted_cmd, cmd_line, i);
	else if (cmd_line[i])
		i = str_token(splitted_cmd, cmd_line, i, env);
	return (i);
}

int	uber_split(char	***splitted_cmd, char *cmd_line, char **env)
{
	int		i;

	i = 0;
	*splitted_cmd = NULL;
	while (cmd_line[i])
	{
		while (cmd_line[i] && cmd_line[i] == 32)
			i++;
		if (cmd_line[i])
			i = create_token(splitted_cmd, cmd_line, i, env);
		if (i == -1)
		{
			free_matrix(*splitted_cmd);
			*splitted_cmd = NULL;
			return (i);
		}
	}
	return (0);
}
