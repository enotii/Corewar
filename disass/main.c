/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:43:14 by ilya              #+#    #+#             */
/*   Updated: 2020/06/21 18:06:39 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int					get_type_by_command(int command)
{
	if (op_tab[command].valid_arg_types[0] & T_DIR)
		return (DIRECT);
	else if (op_tab[command].valid_arg_types[0] & T_IND)
		return (INDIRECT);
	else
		return (REGISTER);
}

t_command_list		*next_disass_command(char *file, int *i, int endianess)
{
	t_command_list	*ret;
	int				count;

	count = 0;
	ret = malloc(sizeof(t_command));
	ret->next = NULL;
	ret->command.is_label = 0;
	ret->command.op_code = (int)file[*i];
	(*i)++;
	if (op_tab[ret->command.op_code - 1].arg_types_code)
	{
		ret->command.types[0] = get_identifier((file[*i] >> 6) & 0x3);
		ret->command.types[1] = get_identifier((file[*i] >> 4) & 0x3);
		ret->command.types[2] = get_identifier((file[*i] >> 2) & 0x3);
		(*i)++;
	}
	else
		ret->command.types[0] = get_type_by_command(ret->command.op_code - 1);
	while (count < op_tab[ret->command.op_code - 1].args_num)
	{
		if (ret->command.types[count] == INDIRECT)
		{
			ret->command.values[count] = transform_int_16(*(int16_t*)\
			(&file[*i]), endianess);
			*i += 2;
		}
		else if (ret->command.types[count] == DIRECT)
		{
			if (op_tab[ret->command.op_code - 1].t_dir_size)
				ret->command.values[count] = transform_int_16(*(int16_t*)\
				(&file[*i]), endianess);
			else
				ret->command.values[count] = transform_int_32(*(int32_t*)\
				(&file[*i]), endianess);
			*i += op_tab[ret->command.op_code - 1].t_dir_size ? 2 : 4;
		}
		else if (ret->command.types[count] == REGISTER)
		{
			ret->command.values[count] = file[*i];
			*i += 1;
		}
		count++;
	}
	return (ret);
}

void				print_commands_to_file(t_command_list *list, int fd)
{
	int i;

	i = 1;
	while (list)
	{
		dprintf(fd, "%s ", op_tab[list->command.op_code - 1].op_name);
		while (i < op_tab[list->command.op_code - 1].args_num)
		{
			if (list->command.types[i] == INDIRECT)
				dprintf(fd, "%d", list->command.values[i]);
			else if (list->command.types[i] == DIRECT)
				dprintf(fd, "%c%d", DIRECT_CHAR, list->command.values[i]);
			else if (list->command.types[i] == REGISTER)
				dprintf(fd, "r%d", list->command.values[i]);
			if (i != op_tab[list->command.op_code - 1].args_num - 1)
				dprintf(fd, ", ");
			i++;
		}
		dprintf(fd, "\n");
		list = list->next;
	}
}

void				disass(char *file, int fd, int size)
{
	int				endianess;
	int				i;
	t_command_list	*next;
	t_command_list	*list;
	t_command_list	*last;

	endianess = check_endianess();
	dprintf(fd, NAME_CMD_STRING);
	dprintf(fd, " \"%s\"\n", &(file[4]));
	dprintf(fd, COMMENT_CMD_STRING);
	dprintf(fd, " \"%s\"\n", &(file[12 + PROG_NAME_LENGTH]));
	list = NULL;
	last = NULL;
	i = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	while (i < size)
	{
		next = next_disass_command(file, &i, endianess);
		if (list == NULL)
		{
			list = next;
			last = next;
		}
		else
		{
			last->next = next;
			last = next;
		}
	}
	print_commands_to_file(list, fd);
}

int					main(int argc, char **argv)
{
	char	*file;
	int		size;
	int		fd;

	size = 0;
	file = parse_bytecode(argv[argc - 1], &size);
	fd = open("new_file.s", O_CREAT | O_RDWR);
	disass(file, fd, size);
	free(file);
	return (0);
}
