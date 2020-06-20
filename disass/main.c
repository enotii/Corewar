/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:43:14 by ilya              #+#    #+#             */
/*   Updated: 2020/06/20 20:06:47 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int16_t			transform_int_16(int16_t integer, int is_big)
{
	if (!is_big)
	{
		int16_t	new_integer = 0;
		new_integer |= (0x00FF & integer) << 8;
		new_integer |= (0xFF00 & integer) >> 8;
		integer = new_integer;
	}
	return (integer);
}

int32_t			transform_int_32(int32_t integer, int is_big)
{
	if (!is_big)
	{
		int32_t	new_integer = 0;
		new_integer |= (0x000000FF & integer) << 24;
		new_integer |= (0x0000FF00 & integer) << 8;
		new_integer |= (0x00FF0000 & integer) >> 8;
		new_integer |= (0xFF000000 & integer) >> 24;
		integer = new_integer;
	}
	return (integer);
}

int				check_endianess()
{
	uint16_t	x;

	x = 1;
	return (*(uint8_t*)&x == 0 ? 1 : 0);
}

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
		new_str = (char*)malloc(*size + num + 1);
		ft_memcpy(new_str, content, *size);
		ft_memcpy(new_str + *size, buffer, num);
		new_str[*size + num] = '\0';
		free(content);
		content = new_str;
		*size += num;
	}
	return (new_str);
}

int			get_identifier(int op_code)
{
	if (op_code == 3)
		return (INDIRECT);
	else if (op_code == 2)
		return (DIRECT);
	else
		return (REGISTER);
}

int			get_type_by_command(int command)
{
	if (op_tab[command].valid_arg_types[0] & T_DIR)
		return (DIRECT);
	else if (op_tab[command].valid_arg_types[0] & T_IND)
		return (INDIRECT);
	else
		return (REGISTER);
}

t_command_list	*next_disass_command(char* file, int *i, int endianess)
{
	t_command_list *ret = malloc(sizeof(t_command));
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
	for (int count = 0; count < op_tab[ret->command.op_code - 1].args_num; count++)
	{
		if (ret->command.types[count] == INDIRECT)
		{
			ret->command.values[count] = transform_int_16(*(int16_t*)(&file[*i]), endianess);
			*i += 2;
		}
		else if (ret->command.types[count] == DIRECT)
		{
			if (op_tab[ret->command.op_code -1].t_dir_size)
				ret->command.values[count] = transform_int_16(*(int16_t*)(&file[*i]), endianess);
			else
				ret->command.values[count] = transform_int_32(*(int32_t*)(&file[*i]), endianess);
			*i += op_tab[ret->command.op_code -1].t_dir_size ? 2 : 4;
		}
		else if (ret->command.types[count] == REGISTER)
		{
			ret->command.values[count] = file[*i];
			*i += 1;
		}
	}
	return (ret);
}

void	print_commands_to_file(t_command_list *list, int fd)
{
	while (list)
	{
		dprintf(fd, "%s ", op_tab[list->command.op_code - 1].op_name);
		for (int i = 0; i < op_tab[list->command.op_code - 1].args_num; ++i)
		{
			if (list->command.types[i] == INDIRECT)
				dprintf(fd, "%d", list->command.values[i]);
			else if (list->command.types[i] == DIRECT)
				dprintf(fd, "%c%d", DIRECT_CHAR, list->command.values[i]);
			else if (list->command.types[i] == REGISTER)
				dprintf(fd, "r%d", list->command.values[i]);
			if (i != op_tab[list->command.op_code - 1].args_num - 1)
			dprintf(fd, ", ");
		}
		dprintf(fd, "\n");
		list = list->next;
	}
}

void	disass(char *file, int fd, int size)
{
	int		endianess = check_endianess();

	dprintf(fd, NAME_CMD_STRING);
	dprintf(fd, " \"%s\"\n", &(file[4]));
	dprintf(fd, COMMENT_CMD_STRING);
	dprintf(fd, " \"%s\"\n", &(file[12 + PROG_NAME_LENGTH]));
	t_command_list *list = NULL;
	t_command_list *last = NULL;
	int i = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	while (i < size)
	{
		t_command_list	*next = next_disass_command(file, &i, endianess);
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

int main(int argc, char **argv)
{
	char	*file;
	int		size;

	size = 0;
	file = parse_bytecode(argv[argc - 1], &size);
	int		fd = open("new_file.s", O_CREAT | O_RDWR);
	disass(file, fd, size);
	free(file);
	 return (0);
}
