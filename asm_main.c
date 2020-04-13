/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:42:45 by caking            #+#    #+#             */
/*   Updated: 2020/04/13 18:20:19 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_token_list	*file_to_tokens(char *str) //string to prebyte-code
{
	int i = 0;
	while(str[i] && (str[i] != SEPARATOR_CHAR || str[i] != '"' \
	|| str[i] != COMMENT_CHAR || str[i] != LABEL_CHAR || str[i] != ALT_COMMENT_CHAR || str[i] != DIRECT_CHAR \
	|| str[i] != ' ' || str[i] != '\n'))
	{
		i++;
	}
	return (NULL);
}

char			*parse_file(char *filename) //file to string
{
	int		fd = open(filename, O_RDONLY);
	char	*content = NULL;
	char	buffer[1000];
	int		num = 0;

	while (num = read(fd, buffer, 1000) > 0)
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
