/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:42:45 by caking            #+#    #+#             */
/*   Updated: 2020/04/14 23:05:13 by caking           ###   ########.fr       */
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

t_token_list			*get_next_token(char **orig_string)
{
	t_token_list		*ret = malloc(sizeof(t_token_list));
	char				*str = *orig_string;
	char				*substring;
	int i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	int		j = 0;
	while (str[i + j] && (str[i + j] != SEPARATOR_CHAR || str[i + j] != '"' \
	|| str[i + j] != COMMENT_CHAR || str[i + j] != LABEL_CHAR || str[i + j] != ALT_COMMENT_CHAR || str[i + j] != DIRECT_CHAR \
	|| str[i + j] != ' ' || str[i + j] != '\n'))
		j++;
	if (j)
		substring = malloc(sizeof(char) * j);
	substring = ft_strsub(str, i, j);
	i += j;
	if (ft_strcmp(substring,NAME_CMD_STRING))
		addlstname(ret);
	else if (ft_strcmp(substring,COMMENT_CMD_STRING))
		addlstcomment(ret);
	// else if ()
	else if(str[i + 1] == '"' && substring)
		adds(ret);
	else if 
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
	parse_file(argv[argc - 1]);
	return(0);
}
