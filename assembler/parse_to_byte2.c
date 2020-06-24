/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_byte2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 20:13:27 by caking            #+#    #+#             */
/*   Updated: 2020/06/23 22:54:34 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int				check_endianess(void)
{
	uint16_t	x;

	x = 1;
	return (*(uint8_t*)&x == 0 ? 1 : 0);
}

void			traverse_args_norm(t_command_list *list, char *body,
int *mem_count, int count)
{
	int			endianess;

	endianess = check_endianess();
	if (g_op_tab[list->command.op_code - 1].t_dir_size)
		*(int16_t*)(&body[*mem_count]) =
		transform_int_16((int16_t)list->command.
		values[count], endianess);
	else
		*(int32_t*)(&body[*mem_count]) =
		transform_int_32((int32_t)list->command.
		values[count], endianess);
	*mem_count += g_op_tab[list->command.op_code - 1].
	t_dir_size ? 2 : 4;
}

void			traverse_args(t_command_list *list,
char *body, int *mem_count, int endianess)
{
	int		count;

	count = 0;
	while (count < g_op_tab[list->command.op_code - 1].args_num)
	{
		if (list->command.types[count] == REGISTER)
		{
			body[*mem_count] = (char)list->command.values[count];
			*mem_count += 1;
		}
		else if (list->command.types[count] == INDIRECT
		|| list->command.types[count] == INDIRECT_LABEL)
		{
			*(int16_t*)(&body[*mem_count]) =
			transform_int_16((int16_t)list->command.values[count], endianess);
			*mem_count += 2;
		}
		else if (list->command.types[count] == DIRECT
		|| list->command.types[count] == DIRECT_LABEL)
			traverse_args_norm(list, body, mem_count, count);
		count++;
	}
}

void			norm_to_bytecode(t_program program, char *body,
int *mem_count, int endianess)
{
	t_command_list *list;

	list = program.list;
	while (list)
	{
		if (!list->command.is_label)
		{
			body[*mem_count] = (char)list->command.op_code;
			(*mem_count)++;
			if (g_op_tab[list->command.op_code - 1].arg_types_code)
			{
				body[*mem_count] = form_byte_args(&list->command);
				(*mem_count)++;
			}
			traverse_args(list, body, mem_count, endianess);
		}
		list = list->next;
	}
}

char			*commands_to_bytecode(t_program program, char *filename)
{
	int			endianess;
	char		body[program.header.prog_size];
	int			mem_count;
	int			fd;

	fd = open_file(filename);
	endianess = check_endianess();
	mem_count = 0;
	prepare_header(body, endianess, program);
	mem_count += 16 + COMMENT_LENGTH + PROG_NAME_LENGTH;
	norm_to_bytecode(program, body, &mem_count, endianess);
	write(fd, body, program.header.prog_size);
	ft_putstr("File ");
	ft_putstr(filename);
	ft_putstr(" assembled succesfully\n");
	free_commands(program.list);
	return (NULL);
}
