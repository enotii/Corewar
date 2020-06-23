/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 22:23:31 by caking            #+#    #+#             */
/*   Updated: 2020/06/23 22:32:27 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int					addstring(t_token_list *ret, char *str, int *countstr)
{
	int				end_string;

	end_string = 0;
	ret->token.type = STRING;
	ret->next = NULL;
	while (str[end_string + 1] && str[end_string + 1] != '"')
	{
		if (str[end_string] == '\n')
			(*countstr)++;
		end_string++;
	}
	if (str[end_string])
	{
		ret->token.string = ft_strsub(str, 1, end_string);
		return (end_string + 2);
	}
	else
		return (-1);
}

void				prepare_header(char *body, int endianess, t_program program)
{
	*(int32_t*)body = transform_int_32((int32_t)COREWAR_EXEC_MAGIC, endianess);
	ft_bzero(&body[4], PROG_NAME_LENGTH);
	ft_strcpy(&body[4], program.header.prog_name);
	*(int32_t*)(&body[4 + PROG_NAME_LENGTH]) = (int32_t)0;
	*(int32_t*)(&body[8 + PROG_NAME_LENGTH]) = transform_int_32((int32_t)
	(program.header.prog_size - 16 -
	PROG_NAME_LENGTH - COMMENT_LENGTH), endianess);
	ft_bzero(&body[12 + PROG_NAME_LENGTH], COMMENT_LENGTH);
	ft_strcpy(&body[12 + PROG_NAME_LENGTH], program.header.comment);
	*(int32_t*)(&body[12 + PROG_NAME_LENGTH + COMMENT_LENGTH]) = (int32_t)0;
}
