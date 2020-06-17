/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 23:24:12 by ilya              #+#    #+#             */
/*   Updated: 2020/06/17 23:45:09 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int						addcommand(t_token_list *ret, int j)
{
	ret->token.type = OPERATION;
	ret->token.op_code = op_tab[j - 1].op_code;
	ret->next = NULL;
	return (0);
}

int						addaltcomment(t_token_list *ret, char *str, int *i)
{
	while (str[*i] && str[*i] != '\n')
		++(*i);
	ret->token.type = COMMENT;
	ret->next = NULL;
	return (0);
}

void					norm(t_tokens_stuff *t)
{
	if (!ft_strcmp(t->substring, NAME_CMD_STRING))
		addlstname(t->ret);
	else if (!ft_strcmp(t->substring, COMMENT_CMD_STRING))
		addlstcomment(t->ret);
	else if (t->str[t->i] == LABEL_CHAR)
		addlabel(t->ret, t->substring, &(t->i));
	else if ((t->j = check_commands(t->substring)))
		addcommand(t->ret, t->j);
	else if (t->substring[0] == 'r')
		addregisterarg(t->ret, t->substring);
	else
		addindirectarg(t->ret, t->substring);
}

void					norm2(t_tokens_stuff *t, int *countstr)
{
	if (t->str[t->i] == '"' && !t->substring)
		t->i += addstring(t->ret, &(t->str[t->i]), countstr);
	else if (t->str[t->i] == COMMENT_CHAR || t->str[t->i] == ALT_COMMENT_CHAR)
		addaltcomment(t->ret, t->str, &(t->i));
	else if (t->str[t->i] == SEPARATOR_CHAR)
		addseparator(t->ret, &(t->i));
	else if (t->str[t->i] == DIRECT_CHAR)
		adddirectarg(t->ret, t->str, &(t->i));
	else if (t->str[t->i] == LABEL_CHAR)
		addindirectlabelarg(t->ret, t->str, &(t->i));
}

t_token_list			*get_next_token(char **orig_string)
{
	static int				countstr = 1;
	t_tokens_stuff			t;

	t.ret = malloc(sizeof(t_token_list));
	t.str = *orig_string;
	t.i = 0;
	t.j = 0;
	t.substring = NULL;
	t.i = skip_whitespaces(t.str, &countstr);
	t.j = skip_until_next_token(t.i, t.str);
	if (t.j)
		t.substring = ft_strsub(t.str, t.i, t.j);
	t.i += t.j;
	if (t.substring)
	{
		norm(&t);
		free(t.substring);
	}
	else
		norm2(&t, &countstr);
	t.ret->token.str_num = countstr;
	*orig_string = &t.str[t.i];
	return (t.ret);
}
