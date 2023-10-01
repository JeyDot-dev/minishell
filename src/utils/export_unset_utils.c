/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:28:57 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/09/10 17:30:24 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	super_unset(char ***env, char *new_var)
{
	char *tmp[2];

	tmp[0] = new_var;
	tmp[1] = NULL;
	ft_export(env, tmp);
}
void	super_export(char ***env, char *new_var)
{
	char *tmp[2];

	tmp[0] = new_var;
	tmp[1] = NULL;
	ft_export(env, tmp);
}
void	super_double_export(char ***env, char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	super_export(env, tmp);
	free(tmp);
}
