/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:42:45 by caking            #+#    #+#             */
/*   Updated: 2020/06/23 20:46:43 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			free_labels(t_label_list *labels)
{
	t_label_list *next;

	while (labels)
	{
		next = labels->next;
		free(labels->label_name);
		free(labels);
		labels = next;
	}
}

void			token_copy(t_token_list *tokens_copy, t_program *result)
{
	t_command_list	*last;
	t_label_list	*last_label;
	t_command_list	*next;

	last = NULL;
	last_label = NULL;
	while (tokens_copy)
	{
		next = get_next_command(&tokens_copy, result, &last_label);
		if (result->list == NULL)
		{
			result->list = next;
			last = next;
		}
		else
		{
			last->next = next;
			last = next;
		}
	}
}

t_program		tokens_to_commands(t_token_list *tokens)
{
	t_program		result;
	t_token_list	*tokens_copy;

	tokens_copy = tokens;
	result.list = NULL;
	result.labels = NULL;
	result.header.prog_size = 0;
	handle_name(&tokens_copy, &result);
	handle_comment(&tokens_copy, &result);
	token_copy(tokens_copy, &result);
	replace_labels_with_values(&result);
	result.header.prog_size += 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	free_tokens(tokens);
	free_labels(result.labels);
	return (result);
}

char			*parse_file(char *filename)
{
	int		fd;
	char	*content;
	char	buffer[1000];
	int		num;
	char	*new_str;

	fd = open(filename, O_RDONLY);
	content = NULL;
	if (fd <= 0)
	{
		ft_putstr("File does not exist");
		exit(0);
	}
	while ((num = read(fd, buffer, 1000)) > 0)
	{
		new_str = (char*)malloc(ft_strlen(content) + num + 1);
		ft_memcpy(new_str, content, ft_strlen(content));
		ft_memcpy(new_str + ft_strlen(content), buffer, num);
		new_str[ft_strlen(content) + num] = '\0';
		free(content);
		content = new_str;
	}
	new_str = ft_strtrim(content);
	free(content);
	return (new_str);
}

int				main(int argc, char **argv)
{
	int	name_len;

	name_len = ft_strlen(argv[argc - 1]);
	if (name_len < 3 || argv[argc - 1][name_len - 1] != 's' ||
	argv[argc - 1][name_len - 2] != '.')
		ft_putstr("Invalid file :c");
	else
		commands_to_bytecode(tokens_to_commands(\
		file_to_tokens(parse_file(argv[argc - 1]))), argv[argc - 1]);
	return (0);
}
