/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:42:45 by caking            #+#    #+#             */
/*   Updated: 2020/04/23 21:13:24 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*commands_to_bytecode(t_program program)
{
	return (NULL);
}

void			handle_name(t_token_list **tokens, t_program *program)
{
	if (!tokens || !((*tokens)->next))
	{
		ft_putstr("Something bad happened\n");
		exit (0);
	}
	if ((*tokens)->token.type != NAME_CMD_STRING)
	{
		ft_putstr("No .name token\n");
		exit (0);
	}
	if ((*tokens)->next->token.type != STRING)
	{
		ft_putstr("No name string\n");
		exit (0);
	}
	ft_strncpy(program->header.prog_name, (*tokens)->next->token.string, PROG_NAME_LENGTH);
	*tokens = (*tokens)->next->next;
}

void			handle_comment(t_token_list **tokens, t_program *program)
{
	if (!tokens || !((*tokens)->next))
	{
		ft_putstr("Something bad happened\n");
		exit (0);
	}
	if ((*tokens)->token.type != COMMENT_CMD_STRING)
	{
		ft_putstr("No .comment token\n");
		exit (0);
	}
	if ((*tokens)->next->token.type != STRING)
	{
		ft_putstr("No name string\n");
		exit (0);
	}
	ft_strncpy(program->header.comment, (*tokens)->next->token.string, COMMENT_LENGTH);
	*tokens = (*tokens)->next->next;
}

void			manage_args(t_token_list **list, t_command_list *result)
{
	int			op_code = (*list)->token.op_code;
	int			count;

	*list = (*list)->next;
	count = 0;
	while (count < op_tab[op_code - 1].args_num)
	{

	}
}

t_command_list	*get_next_command(t_token_list **list)
{
	t_command_list *result = malloc(sizeof(t_command_list));
	if ((*list)->token.type == LABEL)
		result->command.is_label = 1;
	else
	{
		if ((*list)->token.type != OPERATION)
		{
			ft_putstr("Sintaxic error\n");
			exit (0);
		}
		manage_args(list, result);
	}
	return (result);
}

t_program		tokens_to_commands(t_token_list *tokens)
{
	t_program		result;
	t_token_list	*tokens_copy;

	tokens_copy = tokens;
	result.list = NULL;
	handle_name(&tokens_copy, &result);
	handle_comment(&tokens_copy, &result);
	t_command_list	*last = NULL;
	while (tokens_copy)
	{
		t_command_list	*next = get_next_command(&tokens_copy);
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
	return (result);
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
	return (commands_to_bytecode(tokens_to_commands(file_to_tokens(content))));
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
	name_len = ft_strlen(argv[argc - 1]);
	if (name_len < 3 || argv[argc - 1][name_len - 1] != 's' ||
	argv[argc - 1][name_len - 2] != '.')
		ft_putstr("Invalid file :c");
	else
		parse_file(argv[argc - 1]);
	return(0);
}
