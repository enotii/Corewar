/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:43:14 by ilya              #+#    #+#             */
/*   Updated: 2020/06/22 21:00:00 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void				set_arg_types(t_command_list *ret, char *file, int *i)
{
	if (op_tab[ret->command.op_code - 1].arg_types_code)
	{
		ret->command.types[0] = get_identifier((file[*i] >> 6) & 0x3);
		ret->command.types[1] = get_identifier((file[*i] >> 4) & 0x3);
		ret->command.types[2] = get_identifier((file[*i] >> 2) & 0x3);
		(*i)++;
	}
	else
		ret->command.types[0] = get_type_by_command(ret->command.op_code - 1);
}

void				set_args(t_command_list *ret,
char *file, int *i, int endianess)
{
	int				count;

	count = 0;
	while (count < op_tab[ret->command.op_code - 1].args_num)
	{
		if (ret->command.types[count] == INDIRECT)
			ret->command.values[count] = transform_int_16(*(int16_t*)\
			(&file[*i]), endianess);
		else if (ret->command.types[count] == DIRECT)
		{
			ret->command.values[count] =
			op_tab[ret->command.op_code - 1].t_dir_size ?
			transform_int_16(*(int16_t*)(&file[*i]), endianess) :
			transform_int_32(*(int32_t*)(&file[*i]), endianess);
			*i += op_tab[ret->command.op_code - 1].t_dir_size ? 2 : 4;
		}
		else if (ret->command.types[count] == REGISTER)
			ret->command.values[count] = file[*i];
		*i += ret->command.types[count] == INDIRECT ? 2 : 0;
		*i += ret->command.types[count] == REGISTER ? 1 : 0;
		count++;
	}
}

t_command_list		*next_disass_command(char *file, int *i, int endianess)
{
	t_command_list	*ret;

	ret = malloc(sizeof(t_command_list));
	ret->next = NULL;
	ret->command.op_code = (int)file[*i];
	(*i)++;
	set_arg_types(ret, file, i);
	set_args(ret, file, i, endianess);
	return (ret);
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
