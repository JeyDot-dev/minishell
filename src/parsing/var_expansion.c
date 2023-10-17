/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:02:59 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/01 18:35:29 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	skip_dollar(char *str, int i, int mode)
{
	if (mode == 1)
	{
		while (str[i] && str[i] != '$' && !is_meta(str[i])
			&& str[i] != '\'' && str[i] != '\"' && str[i] != 32)
			i++;
	}
	else
	{
		while (str[i] && str[i] == '$')
			i++;
	}
	return (i);
}

int	expand_var(char *str, char **var, int i, char **env)
{
	int		start;
	char	*buffer;
	char	*new_var;

	i = skip_dollar(str, i, 0);
	start = i;
	if (!str[i])
		*var = ft_strdup("$");
	else if (str[i] == '?')
		*var = ft_itoa(g_status);
	if (str[i] == '?')
		i++;
	else
	{
		i = skip_dollar(str, i, 1);
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
	free(str);
	return (new_s);
}
