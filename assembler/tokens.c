/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 23:24:12 by ilya              #+#    #+#             */
/*   Updated: 2020/05/02 19:55:09 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					puterror(int i)
{
	i == LABEL_ERROR ? ft_putstr("INVALID LABEL") : 0;
	i == REGISTER_ERROR ? ft_putstr("INVALID REGISTER ARG") : 0;
	i == LEXIC_ERROR ? ft_putstr("LEXIC ERROR") : 0;

	exit(-1);
}

void					addlstname(t_token_list	*ret)
{
	ret->token.type = CHAMP_NAME;
	ret->next = NULL;
}

void					addlstcomment(t_token_list	*ret)
{
	ret->token.type = CHAMP_COMMENT;
	ret->next = NULL;
}

void					addseparator(t_token_list	*ret, int *i)
{
	ret->token.type = SEPARATOR;
	ret->next = NULL;
	*i = *i + 1;
}

int						skip_whitespaces(char *str, int *countstr)
{
	int i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r')){
		if(str[i] == '\n'){
			(*countstr)++;
		}
		i++;
	}
	return (i);
}

int						skip_until_next_token(int i, char *str)
{
	int					j = 0;
	while (str[i + j] && str[i + j] != SEPARATOR_CHAR && str[i + j] != '"'
	&& str[i + j] != COMMENT_CHAR && str[i + j] != LABEL_CHAR && str[i + j] != ALT_COMMENT_CHAR && str[i + j] != DIRECT_CHAR
	&& str[i + j] != ' ' && str[i + j] != '\t' && str[i + j] != '\n'
	&& str[i + j] != '\v' && str[i + j] != '\f' && str[i + j] != '\r')
		j++;
	return (j);
}

int						addstring(t_token_list *ret, char *str, int *countstr)
{
	int					end_string;

	end_string = 0;

	ret->token.type = STRING;
	ret->next = NULL;
	while (str[end_string + 1] && str[end_string + 1] != '"')
	{
		if(str[end_string] == '\n')
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

int						addlabel(t_token_list *ret, char *substring, int *i)
{
	int j = 0;
	ret->token.type = LABEL;
	while(substring[j])
	{
		if (!ft_strchr(LABEL_CHARS, substring[j]))
			return(puterror(LABEL_ERROR));
		j++;
	}
	ret->token.label = ft_strdup(substring);
	ret->next = NULL;
	*i += 1;
	return (1);
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

int						addcommand(t_token_list *ret, int j)
{
	ret->token.type = OPERATION;
	ret->token.op_code = op_tab[j - 1].op_code;
	ret->next = NULL;
	return (0);
}

int						adddirectarg(t_token_list *ret, char *str, int *i)
{
	(*i)++;
	if (str[*i] == LABEL_CHAR)
	{
		ret->token.type = DIRECT_LABEL;
		(*i)++;
		int				j = skip_until_next_token(*i, str);
		char			*substring = ft_strsub(str, *i, j);
		while(substring[j])
		{
			if (!ft_strchr(LABEL_CHARS, substring[j]))
				return(puterror(LABEL_ERROR));
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
	return(0);
}

int						addregisterarg(t_token_list *ret, char *substring)
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
			return(puterror(REGISTER_ERROR));
		count++;
	}
	return (0);
}

int						addindirectarg(t_token_list *ret, char *substring)
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
	return(0);
}

int						addindirectlabelarg(t_token_list *ret, char *str, int *i)
{
	ret->token.type = INDIRECT_LABEL;
	(*i)++;
	int				j = skip_until_next_token(*i, str);
	char			*substring = ft_strsub(str, *i, j);
	while(substring[j])
	{
		if (!ft_strchr(LABEL_CHARS, substring[j]))
			return(puterror(LABEL_ERROR));
		j++;
	}
	ret->token.indirect_label = substring;
	*i += j;
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

void			norm(t_tokens_stuff			*t)
{
	if (!ft_strcmp(t->substring, NAME_CMD_STRING))
		addlstname(t->ret);
	else if (!ft_strcmp(t->substring ,COMMENT_CMD_STRING))
		addlstcomment(t->ret);
	else if(t->str[t->i] == LABEL_CHAR)
		addlabel(t->ret, t->substring, &(t->i));
	else if ((t->j = check_commands(t->substring)))
		addcommand(t->ret, t->j);
	else if(t->substring[0] == 'r')
		addregisterarg(t->ret, t->substring);
	else
		addindirectarg(t->ret, t->substring);
}

void			norm2(t_tokens_stuff	*t, int *countstr)
{
	if (t->str[t->i] == '"' && !t->substring)
		t->i += addstring(t->ret, &(t->str[t->i]), countstr);
	else if (t->str[t->i] == COMMENT_CHAR || t->str[t->i] == ALT_COMMENT_CHAR)
		addaltcomment(t->ret, t->str, &(t->i));
	else if (t->str[t->i] == SEPARATOR_CHAR)
		addseparator(t->ret, &(t->i));
	else if(t->str[t->i] == DIRECT_CHAR)
		adddirectarg(t->ret, t->str, &(t->i));
	else if(t->str[t->i] == LABEL_CHAR)
		addindirectlabelarg(t->ret, t->str, &(t->i));
}

t_token_list				*get_next_token(char **orig_string)
{
	static int				countstr = 1;
	t_tokens_stuff			t;

	t.ret = malloc(sizeof(t_token_list));
	t.str = *orig_string;
	t.i = 0;
	t.j = 0;
	t.substring = NULL;
	t.i =	skip_whitespaces(t.str, &countstr);
	t.j = skip_until_next_token(t.i, t.str);
	if (t.j)
		t.substring = ft_strsub(t.str, t.i, t.j);
	t.i += t.j;
	if(t.substring)
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

t_token_list		*file_to_tokens(char *str) //string to prebyte-code
{
	char			*str_double;
	t_token_list	*list;
	t_token_list	*list_last;

	str_double = str;
	list = NULL;
	list_last = NULL;
	while (*str)
	{
		t_token_list	*next = get_next_token(&str);
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
