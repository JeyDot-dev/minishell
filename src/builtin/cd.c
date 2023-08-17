/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:54:44 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/08/17 19:47:58 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char	*path)
{
	if (path && *path)
	{
		if(chdir(path))
			perror("cd");
	}
	else if (!path)
	{
		if(chdir(getenv("HOME")))
			perror("cd");
	}
}
