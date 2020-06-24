/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:59:50 by caking            #+#    #+#             */
/*   Updated: 2020/06/23 22:17:32 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int16_t			transform_int_16(int16_t integer, int is_big)
{
	int16_t	new_integer;

	if (!is_big)
	{
		new_integer = 0;
		new_integer |= (0x00FF & integer) << 8;
		new_integer |= (0xFF00 & integer) >> 8;
		integer = new_integer;
	}
	return (integer);
}

int32_t			transform_int_32(int32_t integer, int is_big)
{
	int32_t	new_integer;

	if (!is_big)
	{
		new_integer = 0;
		new_integer |= (0x000000FF & integer) << 24;
		new_integer |= (0x0000FF00 & integer) << 8;
		new_integer |= (0x00FF0000 & integer) >> 8;
		new_integer |= (0xFF000000 & integer) >> 24;
		integer = new_integer;
	}
	return (integer);
}

void			free_commands(t_command_list *list)
{
	t_command_list *next;

	while (list)
	{
		next = list->next;
		if (!list->command.is_label)
		{
			free(list->command.labels[0]);
			free(list->command.labels[1]);
			free(list->command.labels[2]);
		}
		free(list);
		list = next;
	}
}

char			form_byte_args(t_command *command)
{
	char		args[3];
	int			count;

	count = 0;
	while (count < g_op_tab[command->op_code - 1].args_num)
	{
		if (command->types[count] == INDIRECT_LABEL
		|| command->types[count] == INDIRECT)
			args[count] = 3;
		else if (command->types[count] == DIRECT_LABEL
		|| command->types[count] == DIRECT)
			args[count] = 2;
		else if (command->types[count])
			args[count] = 1;
		count++;
	}
	return (args[0] << 6 | args[1] << 4 | args[2] << 2);
}

int				open_file(char *filename)
{
	char		*new_filename;
	char		*split;
	int			fd;

	split = ft_strsplitlast(filename, '/');
	new_filename = malloc(ft_strlen(filename) + 3);
	ft_strcpy(new_filename, split);
	ft_memcpy(&new_filename[ft_strlen(split) - 1], "cor\0", 4);
	free(split);
	fd = open(new_filename, O_CREAT | O_RDWR);
	free(new_filename);
	return (fd);
}
