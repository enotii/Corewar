/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_func2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 23:14:18 by caking            #+#    #+#             */
/*   Updated: 2020/06/17 23:46:57 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int						addlabel(t_token_list *ret, char *substring, int *i)
{
	int j;

	j = 0;
	ret->token.type = LABEL;
	while (substring[j])
	{
		if (!ft_strchr(LABEL_CHARS, substring[j]))
			return (puterror(LABEL_ERROR));
		j++;
	}
	ret->token.label = ft_strdup(substring);
	ret->next = NULL;
	*i += 1;
	return (1);
}

int						skip_until_next_token(int i, char *str)
{
	int					j;

	j = 0;
	while (str[i + j] && str[i + j] != SEPARATOR_CHAR && str[i + j] != '"'
	&& str[i + j] != COMMENT_CHAR && str[i + j] != LABEL_CHAR
	&& str[i + j] != ALT_COMMENT_CHAR && str[i + j] != DIRECT_CHAR
	&& str[i + j] != ' ' && str[i + j] != '\t' && str[i + j] != '\n'
	&& str[i + j] != '\v' && str[i + j] != '\f' && str[i + j] != '\r')
		j++;
	return (j);
}

int						check_commands(char *substring)
{
	int					i;

	i = -1;
	while (++i < 17)
		if (!ft_strcmp(op_tab[i].op_name, substring))
			return (i + 1);
	return (0);
}

t_token_list			*file_to_tokens(char *str)
{
	char			*str_double;
	t_token_list	*list;
	t_token_list	*list_last;
	t_token_list	*next;

	str_double = str;
	list = NULL;
	list_last = NULL;
	while (*str)
	{
		next = get_next_token(&str);
		if (next->token.type == COMMENT)
		{
			free(next);
			continue ;
		}
		if (list == NULL)
			list = next;
		else
			list_last->next = next;
		list_last = next;
	}
	free(str_double);
	return (list);
}
