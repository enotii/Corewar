/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:42:45 by caking            #+#    #+#             */
/*   Updated: 2020/06/18 20:33:22 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			free_tokens(t_token_list *tokens)
{
	t_token_list *next;

	while (tokens)
	{
		next = tokens->next;
		if (tokens->token.type == STRING)
			free(tokens->token.string);
		else if (tokens->token.type == LABEL)
			free(tokens->token.label);
		else if (tokens->token.type == INDIRECT_LABEL)
			free(tokens->token.indirect_label);
		else if (tokens->token.type == DIRECT_LABEL)
			free(tokens->token.direct_label);
		free(tokens);
		tokens = next;
	}
}

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

t_program		tokens_to_commands(t_token_list *tokens)
{
	t_program		result;
	t_token_list	*tokens_copy;
	t_command_list	*last;
	t_label_list	*last_label;
	t_command_list	*next;

	tokens_copy = tokens;
	result.list = NULL;
	result.labels = NULL;
	result.header.prog_size = 0;
	handle_name(&tokens_copy, &result);
	handle_comment(&tokens_copy, &result);
	last = NULL;
	last_label = NULL;
	while (tokens_copy)
	{
		next = get_next_command(&tokens_copy, &result, &last_label);
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
	num = 0;
	new_str = NULL;
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
