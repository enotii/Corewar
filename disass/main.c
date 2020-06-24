/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:43:14 by ilya              #+#    #+#             */
/*   Updated: 2020/06/23 23:22:54 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void				set_arg_types(t_command_list *ret, char *file, int *i)
{
	if (g_op_tab[ret->command.op_code - 1].arg_types_code)
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
	while (count < g_op_tab[ret->command.op_code - 1].args_num)
	{
		if (ret->command.types[count] == INDIRECT)
			ret->command.values[count] = transform_int_16(*(int16_t*)\
			(&file[*i]), endianess);
		else if (ret->command.types[count] == DIRECT)
		{
			ret->command.values[count] =
			g_op_tab[ret->command.op_code - 1].t_dir_size ?
			transform_int_16(*(int16_t*)(&file[*i]), endianess) :
			transform_int_32(*(int32_t*)(&file[*i]), endianess);
			*i += g_op_tab[ret->command.op_code - 1].t_dir_size ? 2 : 4;
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

int					open_file_dasm(char *filename)
{
	char		*new_filename;
	char		*split;
	int			fd;

	split = ft_strsplitlast(filename, '/');
	new_filename = malloc(ft_strlen(filename) - 2);
	ft_strcpy(new_filename, split);
	ft_memcpy(&new_filename[ft_strlen(split) - 3], "s\0", 2);
	free(split);
	fd = open(new_filename, O_CREAT | O_RDWR);
	free(new_filename);
	return (fd);
}

int					main(int argc, char **argv)
{
	char	*file;
	int		size;
	int		fd;
	int		name_len;

	name_len = ft_strlen(argv[argc - 1]);
	if (name_len < 3 || argv[argc - 1][name_len - 1] != 'r' ||
	argv[argc - 1][name_len - 2] != 'o' || argv[argc - 1][name_len - 3] != 'c'
	|| argv[argc - 1][name_len - 4] != '.')
		ft_putstr("Invalid file :c");
	else
	{
		size = 0;
		file = parse_bytecode(argv[argc - 1], &size);
		fd = open_file_dasm(argv[argc - 1]);
		disass(file, fd, size);
		free(file);
	}
	return (0);
}
