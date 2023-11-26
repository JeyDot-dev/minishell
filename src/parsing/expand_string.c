/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:02:59 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 17:12:51 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*free_old_return_new(char *str, char *new_s)
{
	free(str);
	return (new_s);
}

int	make_func_shorter(char **old, char *new, int ret)
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
		start = make_func_shorter(&new_s, ft_strndup(&str[start],
					end - start), end);
	}
	return (free_old_return_new(str, new_s));
}
