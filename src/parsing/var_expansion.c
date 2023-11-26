/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:02:59 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 11:54:14 by jsousa-a         ###   ########.fr       */
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

int	expand_var(char *str, char **var, int i, t_shell *shell)
{
	int		start;
	char	*buffer;
	char	*new_var;

	i = skip_dollar(str, i, 0);
	start = i;
	if (!str[i])
		*var = ft_strdup("$");
	else if (str[i] == '?')
		*var = ft_itoa(shell->last_cmd_status);
	if (str[i] == '?')
		i++;
	else
	{
		i = skip_dollar(str, i, 1);
		buffer = ft_strndup(&str[start], i - start);
		new_var = getvar_data(shell->env, buffer);
		ft_memdel(buffer);
		if (new_var)
			*var = ft_strdup(new_var);
//		ft_memdel(new_var);
	}
	return (i);
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*new_s;
	char	*var;
	int		start;
	int		end;

	new_s = NULL;
	start = 0;
	end = 0;
	if (!str)
		return (NULL);
	while (str[start])
	{
		var = NULL;
		if (str[start] == '$')
		{
			start = expand_var(str, &var, end, shell);
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
