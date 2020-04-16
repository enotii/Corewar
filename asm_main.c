/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:42:45 by caking            #+#    #+#             */
/*   Updated: 2020/04/16 22:57:14 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

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
	while (str[i + j] && (str[i + j] != SEPARATOR_CHAR || str[i + j] != '"' \
	|| str[i + j] != COMMENT_CHAR || str[i + j] != LABEL_CHAR || str[i + j] != ALT_COMMENT_CHAR || str[i + j] != DIRECT_CHAR \
	|| str[i + j] != ' ' || str[i + j] != '\n'))
		j++;
	return (j);
}

int						addstring(t_token_list *list, char *str)
{
	int					end_string;

	end_string = 1;

	while (str[end_string] && str[end_string] != '"')
		end_string++;
	if (str[end_string])
		return (end_string + 1);
	else
		return (-1);
}

t_token_list			*get_next_token(char **orig_string)
{
	t_token_list		*ret = malloc(sizeof(t_token_list));
	char				*str = *orig_string;
	char				*substring;
	int 				i = 0;
	int					j = 0;

	i =	skip_whitespaces(str);
	j = skip_until_next_token(i, str);
	if (j)
		substring = malloc(sizeof(char) * j);
	substring = ft_strsub(str, i, j);
	i += j;
	if (ft_strcmp(substring, NAME_CMD_STRING))
		addlstname(ret);
	else if (ft_strcmp(substring ,COMMENT_CMD_STRING))
		addlstcomment(ret);
	else if (str[i] == '"' && !substring)
		i += addstring(ret, str);
	else if (str[i] == COMMENT_CHAR || str[i] == ALT_COMMENT_CHAR)
		while (str[i] && str[i] != '\n')
			++i;
	else if (str[i] == SEPARATOR_CHAR)
		addseparator(ret, &i);
	else if (str[i] == '\n')
		i++;
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
	
	name_len = ft_strlen(argv[argc - 1]);
	if (name_len < 3 || argv[argc - 1][name_len - 1] != 's' ||
	argv[argc - 1][name_len - 2] != '.')
		ft_putstr("Invalid file :c");
	else
		parse_file(argv[argc - 1]);
	return(0);
}
