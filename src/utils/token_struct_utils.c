/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsousa-a <jsousa-a@student.42lausan>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:25:18 by jsousa-a          #+#    #+#             */
/*   Updated: 2023/11/26 19:03:37 by jsousa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_tokens	*find_last(t_tokens *list)
{
	t_tokens	*tmp;

	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	add_token(char *token, int is_meta, t_tokens **token_list)
{
	t_tokens	*tmp;
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (-1);
	new->token = token;
	new->is_meta = is_meta;
	new->next = NULL;
	if (!*token_list)
		*token_list = new;
	else
	{
		tmp = find_last(*token_list);
		tmp->next = new;
	}
	return (0);
}

void	delete_tokens(t_tokens *token_list)
{
	t_tokens	*tmp;

	if (!token_list)
		return ;
	while (token_list)
	{
		tmp = token_list;
		if (tmp->token)
			free(tmp->token);
		token_list = token_list->next;
		free(tmp);
		tmp = token_list;
	}
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
