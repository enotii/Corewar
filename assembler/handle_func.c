/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:22:30 by caking            #+#    #+#             */
/*   Updated: 2020/06/22 21:51:53 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			handle_name(t_token_list **tokens, t_program *program)
{
	if (!tokens || !((*tokens)->next))
	{
		ft_putstr("Something bad happened\n");
		exit(0);
	}
	if ((*tokens)->token.type != CHAMP_NAME)
	{
		ft_putstr("No .name token\n");
		exit(0);
	}
	if ((*tokens)->next->token.type != STRING)
	{
		ft_putstr("No name string\n");
		exit(0);
	}
	ft_strncpy(program->header.prog_name,
	(*tokens)->next->token.string, PROG_NAME_LENGTH);
	*tokens = (*tokens)->next->next;
}

void			handle_comment(t_token_list **tokens, t_program *program)
{
	if (!tokens || !((*tokens)->next))
	{
		ft_putstr("Something bad happened\n");
		exit(0);
	}
	if ((*tokens)->token.type != CHAMP_COMMENT)
	{
		ft_putstr("No .comment token\n");
		exit(0);
	}
	if ((*tokens)->next->token.type != STRING)
	{
		ft_putstr("No name string\n");
		exit(0);
	}
	ft_strncpy(program->header.comment,
	(*tokens)->next->token.string, COMMENT_LENGTH);
	*tokens = (*tokens)->next->next;
}
