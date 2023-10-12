/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:25:18 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/10/12 16:49:38 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token(char *token, int is_meta, t_tokens **token_list)
{
	t_tokens 	*head;
	t_tokens	*new;

	head = *token_list;
	new = malloc(sizeof(*new));
	if (!new)
		return (-1);
	new->token = token;
	new->is_meta = is_meta;
	new->next = NULL;
	if (!*token_list)
	{
		*token_list = new;
	}
	else
	{
			while (head->next)
				head = head->next;
		head->next = new;
	}
	return (0);
}
/*int main(void)
{
	t_tokens *tokens;
	tokens = NULL;
	add_token("WOW", 1, &tokens);
	add_token("WAPITI", 1, &tokens);
	printf("tokens:%s\n", tokens->token);
	tokens = tokens->next;
	printf("tokens:%s\n", tokens->token);
}*/
