/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:23:47 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/28 13:34:43 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_tokens *tokens)
{
	int	ct;

	ct = 0;
	while (tokens)
	{
		if (tokens->is_meta == PIPE)
			ct++;
		tokens = tokens->next;
	}
	return (ct);
}
