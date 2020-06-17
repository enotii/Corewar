/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 23:12:00 by caking            #+#    #+#             */
/*   Updated: 2020/06/17 23:50:20 by caking           ###   ########.fr       */
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

int					adddirectarg(t_token_list *ret, char *str, int *i)
{
	char			*substring;
	int				j;

	(*i)++;
	if (str[*i] == LABEL_CHAR)
	{
		ret->token.type = DIRECT_LABEL;
		(*i)++;
		j = skip_until_next_token(*i, str);
		substring = ft_strsub(str, *i, j);
		while (substring[j])
		{
			if (!ft_strchr(LABEL_CHARS, substring[j]))
				return (puterror(LABEL_ERROR));
			j++;
		}
		ret->token.direct_label = substring;
		*i += j;
	}
	else
	{
		ret->token.direct = ft_atoi(&str[*i]);
		if (str[*i] == '-')
			(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
			(*i)++;
		ret->token.type = DIRECT;
	}
	ret->next = NULL;
	return (0);
}

int					addregisterarg(t_token_list *ret, char *substring)
{
	int					count;
	int					len;

	count = 1;
	len = ft_strlen(substring);
	ret->token.type = REGISTER;
	ret->token.register_num = ft_atoi(&substring[1]);
	ret->next = NULL;
	while (count < len)
	{
		if (substring[count] > '9' || substring[count] < '0')
			return (puterror(REGISTER_ERROR));
		count++;
	}
	return (0);
}

int					addindirectarg(t_token_list *ret, char *substring)
{
	int					j;
	int					len;

	j = 0;
	len = ft_strlen(substring);
	ret->token.indirect = ft_atoi(substring);
	if (substring[0] == '-')
		j++;
	while (j < len)
	{
		if (!(substring[j] >= '0' && substring[j] <= '9'))
			return (puterror(LEXIC_ERROR));
		j++;
	}
	ret->token.type = INDIRECT;
	ret->next = NULL;
	return (0);
}

int					addindirectlabelarg(t_token_list *ret, char *str, int *i)
{
	char			*substring;
	int				j;

	ret->token.type = INDIRECT_LABEL;
	(*i)++;
	j = skip_until_next_token(*i, str);
	substring = ft_strsub(str, *i, j);
	while (substring[j])
	{
		if (!ft_strchr(LABEL_CHARS, substring[j]))
			return (puterror(LABEL_ERROR));
		j++;
	}
	ret->token.indirect_label = substring;
	*i += j;
	return (0);
}
