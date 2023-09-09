/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:15:57 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/09 19:59:57 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}
void printvar(char **env, char *var)
{
	ft_printf("%s\n", getvar(env, var));
}
