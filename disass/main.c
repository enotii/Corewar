/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:43:14 by ilya              #+#    #+#             */
/*   Updated: 2020/06/15 22:05:55 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*parse_bytecode(char *filename, int *size) //file to string
{
	int		fd = open(filename, O_RDONLY);
	char	*content = NULL;
	char	buffer[1000];
	int		num = 0;
	char	*new_str = NULL;

	if (fd <= 0)
	{
		ft_putstr("File does not exist");
		exit (0);
	}
	while ((num = read(fd, buffer, 1000)) > 0)
	{
		new_str = (char*)malloc(ft_strlen(content) + num + 1);
		ft_memcpy(new_str, content, ft_strlen(content));
		ft_memcpy(new_str + ft_strlen(content), buffer, num);
		new_str[ft_strlen(content) + num] = '\0';
		free(content);
		content = new_str;
		*size += num;
	}
	return (new_str);
}

void	disass(char *file, int fd, int size)
{
	fprintf(fd, NAME_CMD_STRING);
	fprintf(fd, " %s\n", &file[4]);
	fprintf(fd, COMMENT_CMD_STRING);
	fprintf(fd, " %s\n", &file[12 + PROG_NAME_LENGTH]);
	t_command_list *list = NULL;
	while (file)
	{
		t_command_list	*next = get_next_command(&tokens_copy, &result, &last_label);
		if (result.list == NULL)
		{
			result.list = next;
			last = next;
		}
		else
		{
			last->next = next;
			last = next;
		}
	}
}

int main(int argc, char **argv)
{
	char	*file;
	int		size;

	size = 0;
	file = parse_bytecode(argv[argc - 1], &size);
	int		fd = open("new_file.s", O_CREAT);
	disass(file, fd, size);
	free(file);
	return (0);
}
