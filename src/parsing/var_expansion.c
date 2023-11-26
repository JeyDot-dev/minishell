/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:02:59 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 15:22:51 by jsousa-a         ###   ########.fr       */
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
int expand_var_extension(char **var, int i)
{
	*var = ft_strdup("$");
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
		return (expand_var_extension(var, i));
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
	}
	return (i);
}

char	*free_old_return_new(char *str, char *new_s)
{
	free(str);
	return (new_s);
}
int		make_func_shorter(char **old, char *new, int ret)
{
	*old = free_join(*old, new);
	return (ret);

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
			end = make_func_shorter(&new_s, var, start);
		}
		while (str[end] && str[end] != '$')
			end++;
		start = make_func_shorter(&new_s, ft_strndup(&str[start], end - start), end);
	}
	return (free_old_return_new(str, new_s));
}
