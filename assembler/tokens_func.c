/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 23:09:19 by caking            #+#    #+#             */
/*   Updated: 2020/06/17 23:34:44 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int						puterror(int i)
{
	i == LABEL_ERROR ? ft_putstr("INVALID LABEL") : 0;
	i == REGISTER_ERROR ? ft_putstr("INVALID REGISTER ARG") : 0;
	i == LEXIC_ERROR ? ft_putstr("LEXIC ERROR") : 0;
	exit(-1);
}

void					addlstname(t_token_list *ret)
{
	ret->token.type = CHAMP_NAME;
	ret->next = NULL;
}

void					addlstcomment(t_token_list *ret)
{
	ret->token.type = CHAMP_COMMENT;
	ret->next = NULL;
}

void					addseparator(t_token_list *ret, int *i)
{
	ret->token.type = SEPARATOR;
	ret->next = NULL;
	*i = *i + 1;
}

int						skip_whitespaces(char *str, int *countstr)
{
	int i;

	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
	|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
	{
		if (str[i] == '\n')
		{
			(*countstr)++;
		}
		i++;
	}
	return (i);
}
