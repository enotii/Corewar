/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:42:45 by caking            #+#    #+#             */
/*   Updated: 2020/04/18 23:43:54 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"


void					puterror(int i)
{
	i == LABEL_ERROR ? ft_putstr("INVALID LABEL") : 0;
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

int						skip_whitespaces(char *str)
{
	int i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
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

int						addstring(t_token_list *ret, char *str)
{
	int					end_string;

	end_string = 0;

	ret->token.type = STRING;
	ret->next = NULL;
	while (str[end_string + 1] && str[end_string + 1] != '"')
		end_string++;
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
		{
			puterror(LABEL_ERROR);
			return (0);
		}
		j++;
	}
	ret->token.label = ft_strdup(substring);
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

t_token_list			*get_next_token(char **orig_string)
{
	t_token_list		*ret = malloc(sizeof(t_token_list));
	char				*str = *orig_string;
	char				*substring;
	int 				i = 0;
	int					j = 0;

	substring = NULL;
	i =	skip_whitespaces(str);
	j = skip_until_next_token(i, str);
	if (j)
		substring = ft_strsub(str, i, j);
	i += j;
	if(substring)
	{
		if (!ft_strcmp(substring, NAME_CMD_STRING))
			addlstname(ret);
		else if (!ft_strcmp(substring ,COMMENT_CMD_STRING))
			addlstcomment(ret);
		else if(str[i] == LABEL_CHAR)
			addlabel(ret, substring, &i);
		else if ((j = check_commands(substring)))
			addcommand(ret, j);
	}
	else
	{
		if (str[i] == '"' && !substring)
			i += addstring(ret, &str[i]);
		else if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
			while (str[i] && str[i] != '\n')
				++i;
		else if (str[i] == SEPARATOR_CHAR)
			addseparator(ret, &i);
	}
	*orig_string = &str[i];
	return (ret);
}

t_token_list		*file_to_tokens(char *str) //string to prebyte-code
{
	t_token_list	*list = NULL;
	t_token_list	*list_last = NULL;
	while (*str)
	{
		t_token_list	*next = get_next_token(&str);
		if (list == NULL)
		{
			list = next;
			list_last = next;
		}
		else
		{
			list_last->next = next;
			list_last = next;
		}
	}
	return (list);
}

char			*parse_file(char *filename) //file to string
{
	int		fd = open(filename, O_RDONLY);
	char	*content = NULL;
	char	buffer[1000];
	int		num = 0;

	while ((num = read(fd, buffer, 1000)) > 0)
	{
		char	*new_str = (char*)malloc(ft_strlen(content) + num + 1);
		ft_memcpy(new_str, content, ft_strlen(content));
		ft_memcpy(new_str + ft_strlen(content), buffer, num);
		new_str[ft_strlen(content) + num] = '\0';
		free(content);
		content = new_str;
	}
	file_to_tokens(content);
	return (NULL);
}

int				main(int argc, char **argv)
{
	int	name_len;
	
//	ft_putnbr(op_tab[0].args_num);
//	ft_putstr(op_tab[0].op_name);
	name_len = ft_strlen(argv[argc - 1]);
	if (name_len < 3 || argv[argc - 1][name_len - 1] != 's' ||
	argv[argc - 1][name_len - 2] != '.')
		ft_putstr("Invalid file :c");
	else
		parse_file(argv[argc - 1]);
	return(0);
}
