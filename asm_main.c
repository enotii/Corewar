/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:42:45 by caking            #+#    #+#             */
/*   Updated: 2020/04/25 16:47:00 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*commands_to_bytecode(t_program program)
{
	char		body[program.header.prog_size];
	int			fd = open(program.header.prog_name, O_CREAT | O_RDWR);

	int			mem_count = 0;
	*(int32_t*)body = (int32_t)COREWAR_EXEC_MAGIC;
	ft_bzero(&body[4], PROG_NAME_LENGTH);
	ft_strcpy(&body[4], program.header.prog_name);
	*(int32_t*)(&body[4 + PROG_NAME_LENGTH]) = (int32_t)0;
	*(int32_t*)(&body[8 + PROG_NAME_LENGTH]) = (int32_t)program.header.prog_size;
	ft_bzero(&body[12 + PROG_NAME_LENGTH], COMMENT_LENGTH);
	ft_strcpy(&body[12 + PROG_NAME_LENGTH], program.header.comment);
	*(int32_t*)(&body[12 + PROG_NAME_LENGTH + COMMENT_LENGTH]) = (int32_t)0;
	mem_count += 16 + COMMENT_LENGTH + PROG_NAME_LENGTH;
	t_command_list *list = program.list;
	while (list)
	{
		if (list->command.is_label)
		{
			list = list->next;
			continue;
		}
		body[mem_count] = (char)list->command.op_code;
		mem_count++;
		if (op_tab[list->command.op_code - 1].arg_types_code)
		{
			body[mem_count] = 0; //PLACEHOLDER!!!
			mem_count++;
		}
		int		count = 0;
		while (count < op_tab[list->command.op_code - 1].args_num)
		{
			if (list->command.types[count] == REGISTER)
			{
				body[mem_count] = (char)list->command.values[count];
				mem_count += 1;
			}
			else if (list->command.types[count] == INDIRECT || list->command.types[count] == INDIRECT_LABEL)
			{
				*(int16_t*)(&body[mem_count]) = (int16_t)list->command.values[count];
				mem_count += 2;
			}
			else if (list->command.types[count] == DIRECT || list->command.types[count] == DIRECT_LABEL)
			{
				if (op_tab[list->command.op_code -1].t_dir_size)
					*(int16_t*)(&body[mem_count]) = (int16_t)list->command.values[count];
				else
					*(int32_t*)(&body[mem_count]) = (int32_t)list->command.values[count];
				mem_count += op_tab[list->command.op_code -1].t_dir_size ? 2 : 4;
			}		
			count++;
		}
		list = list->next;
	}
	write(fd, body, program.header.prog_size);
	return (NULL);
}

void			handle_name(t_token_list **tokens, t_program *program)
{
	if (!tokens || !((*tokens)->next))
	{
		ft_putstr("Something bad happened\n");
		exit (0);
	}
	if ((*tokens)->token.type != CHAMP_NAME)
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
	if ((*tokens)->token.type != CHAMP_COMMENT) 
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

void			manage_args(t_token_list **list, t_command_list *result, t_program *prog)
{
	int			op_code = (*list)->token.op_code;
	int			count;

	*list = (*list)->next;
	count = 0;
	result->command.op_code = op_code;
	while (count < op_tab[op_code - 1].args_num)
	{
		if ((!(op_tab[op_code -1].valid_arg_types[count] & T_REG) && (*list)->token.type == REGISTER)
		|| (!(op_tab[op_code -1].valid_arg_types[count] & T_IND) && ((*list)->token.type == INDIRECT || (*list)->token.type == INDIRECT_LABEL))
		|| (!(op_tab[op_code -1].valid_arg_types[count] & T_DIR) && ((*list)->token.type == DIRECT || (*list)->token.type == DIRECT_LABEL)))
		{
			ft_putstr("Wrong argument\n");
			exit (0);
		}
		result->command.types[count] = (*list)->token.type;
		if ((*list)->token.type == REGISTER)
			result->command.values[count] = (*list)->token.register_num;
		else if ((*list)->token.type == INDIRECT)
			result->command.values[count] = (*list)->token.indirect;
		else if ((*list)->token.type == DIRECT)
			result->command.values[count] = (*list)->token.direct;
		else if ((*list)->token.type == DIRECT_LABEL)
			result->command.labels[count] = ft_strdup((*list)->token.direct_label);
		else if ((*list)->token.type == INDIRECT_LABEL)
			result->command.labels[count] = ft_strdup((*list)->token.indirect_label);

		if ((*list)->token.type == REGISTER)
			prog->header.prog_size += 1;
		else if ((*list)->token.type == INDIRECT || (*list)->token.type == INDIRECT_LABEL)
			prog->header.prog_size += 2;
		else if ((*list)->token.type == DIRECT || (*list)->token.type == DIRECT_LABEL)
			prog->header.prog_size += op_tab[op_code - 1].t_dir_size ? 2 : 4;
		*list = (*list)->next;
		if (count + 1 != op_tab[op_code - 1].args_num)
		{
			if (!(*list) || (*list)->token.type != SEPARATOR)
			{
				ft_putstr("No separator\n");
				exit (0);
			}
			*list = (*list)->next;
		}
		count++;
	}
}

t_command_list	*get_next_command(t_token_list **list, t_program *prog, t_label_list **last_label)
{
	t_command_list *result = malloc(sizeof(t_command_list));
	if ((*list)->token.type == LABEL)
	{
		result->command.is_label = 1;
		t_label_list *next = malloc(sizeof(t_label_list));
		next->label_name = ft_strdup((*list)->token.label);
		next->label_position = prog->header.prog_size;
		next->next = NULL;
		if (prog->labels == NULL)
		{
			prog->labels = next;
			*last_label = next;
		}
		else
		{
			(*last_label)->next = next;
			*last_label = next;
		}
		result->command.is_label = 1;
		*list = (*list)->next;
	}
	else
	{
		if ((*list)->token.type != OPERATION)
		{
			ft_putstr("Sintaxic error\n");
			exit (0);
		}
		prog->header.prog_size += 1;
		prog->header.prog_size += op_tab[(*list)->token.op_code - 1].arg_types_code;
		manage_args(list, result, prog);
	}
	return (result);
}

void			replace_one_label_by_value(t_command *command, int count, t_label_list *list, int bytes)
{
	int found = 0;

	while (list)
	{
		if (!ft_strcmp(list->label_name, command->labels[count]))
		{
			found = 1;
			break;
		}
		list = list->next;
	}
	if (found)
	{
		if (command->types[count] == INDIRECT_LABEL)
			command->values[count] = list->label_position; // PLACEHOLDER !!!
		else
			command->values[count] = list->label_position - bytes; // PLACEHOLDER !!!
	}
	else
	{
		ft_putstr("Reference to undefined label\n");
		exit (0);
	}

}

void			replace_labels_with_values(t_program *prog)
{
	t_command_list	*list = prog->list;
	int				byte_count = 0;

	while (list)
	{
		if (list->command.is_label)
		{
			list = list->next;
			continue;
		}
		int			count = 0;
		byte_count += 1 + op_tab[list->command.op_code -1].arg_types_code;
		while (count < op_tab[list->command.op_code - 1].args_num)
		{
			if (list->command.types[count] == INDIRECT_LABEL || list->command.types[count] == DIRECT_LABEL)
				replace_one_label_by_value(&list->command, count, prog->labels, byte_count);
			if (list->command.types[count] == REGISTER)
				byte_count += 1;
			else if (list->command.types[count] == INDIRECT || list->command.types[count] == INDIRECT_LABEL)
				byte_count += 2;
			else if (list->command.types[count] == DIRECT || list->command.types[count] == DIRECT_LABEL)
				byte_count += op_tab[list->command.op_code -1].t_dir_size ? 2 : 4;
			count++;
		}
		list = list->next;
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
	t_command_list	*last = NULL;
	t_label_list	*last_label = NULL;
	while (tokens_copy)
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
	replace_labels_with_values(&result);
	result.header.prog_size += 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
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
		content = ft_strtrim(new_str);
		free(new_str);
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
