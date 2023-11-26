/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:15:12 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 14:22:25 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == '_')
		return (1);
	else
		return (0);
}

int	check_env_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg || !mini_isalpha(*arg))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", arg);
		return (-1);
	}
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i])
		return (i);
	else
		return (0);
}
