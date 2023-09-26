/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uber_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:00:22 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/26 11:00:24 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
int		is_meta(const int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

char	*free_join(char *str, char *buffer)
{
	char	*new;

	if (str)
		new = ft_strjoin(str, buffer);
	else
		return (buffer);
	if (!new)
		return (NULL);
	str = ft_memdel(str);
	buffer = ft_memdel(buffer);
	return (new);
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

int	expand_var(char *str, char **var, int i, int err, char **env)
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
		*var = ft_strdup(ft_itoa(err));
	else
	{
		while (str[i] && str[i] != '$' && !is_meta(str[i]) &&
				str[i] != '\'' && str[i] != '\"' && str[i] != 32)
			i++;
		buffer = ft_strndup(str, i - start + 1);
		new_var = extract_var_data(getvar(env, buffer));
		ft_memdel(buffer);
		if (new_var)
			*var = ft_strdup(new_var);
		ft_memdel(new_var);
	}
	return (i);
}

char	*expand_string(char *str, int err, char **env)
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
			start = expand_var(str, &var, end, err, env);
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

int		get_string(char *cmd_line, char **buffer, int i, int err, char **env)
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
		*buffer = expand_string(*buffer, err, env);
	if (start[1])
		i++;
	return (i);
}

int		str_token(char ***splitted_cmd, char *cmd_line, int i, int err, char **env)
{
	char	*new_str;
	char	*buffer;

	buffer = NULL;
	new_str = NULL;
	while (is_string(cmd_line[i]))
	{
		i = get_string(cmd_line, &buffer, i, err, env);
		if (i >= 0)
			new_str = free_join(new_str, buffer);
	}
	if (new_str && add_to_matrix(splitted_cmd, new_str) != 0)
		i = -1;
	ft_memdel(new_str);
	return (i);
}
/*
int		meta_token(char ***splitted_cmd, char *cmd_line, int i)
{
	(void) splitted_cmd;
	(void) cmd_line;
	(void) i;
}*/
int		create_token(char ***splitted_cmd, char *cmd_line, int i, int err, char **env)
{
//	if (is_meta(cmd_line[i]))
//		i = meta_token(splitted_cmd, cmd_line, i);
//	else if (cmd_line[i])
	if (cmd_line[i])
		i = str_token(splitted_cmd, cmd_line, i, err, env);
	return (i);
}

int	uber_split(char	***splitted_cmd, char *cmd_line, int err, char **env)
{
	int		i;

	i = 0;
	while (cmd_line[i])
	{
		while (cmd_line[i] && cmd_line[i] == 32)
			i++;
		if (cmd_line[i])
			i = create_token(splitted_cmd, cmd_line, i, err, env);
		if (i == -1)
		{
			free_matrix(*splitted_cmd);
			return (i);
		}
	}
	return (i);
}
