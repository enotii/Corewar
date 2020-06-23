/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disass_func2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 20:14:39 by caking            #+#    #+#             */
/*   Updated: 2020/06/23 22:46:02 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int					get_type_by_command(int command)
{
	if (g_op_tab[command].valid_arg_types[0] & T_DIR)
		return (DIRECT);
	else if (g_op_tab[command].valid_arg_types[0] & T_IND)
		return (INDIRECT);
	else
		return (REGISTER);
}

void				print_commands_to_file(t_command_list *list, int fd)
{
	int i;

	while (list)
	{
		i = 0;
		dprintf(fd, "%s ", g_op_tab[list->command.op_code - 1].op_name);
		while (i < g_op_tab[list->command.op_code - 1].args_num)
		{
			if (list->command.types[i] == INDIRECT)
				dprintf(fd, "%d", list->command.values[i]);
			else if (list->command.types[i] == DIRECT)
				dprintf(fd, "%c%d", DIRECT_CHAR, list->command.values[i]);
			else if (list->command.types[i] == REGISTER)
				dprintf(fd, "r%d", list->command.values[i]);
			if (i != g_op_tab[list->command.op_code - 1].args_num - 1)
				dprintf(fd, ", ");
			i++;
		}
		dprintf(fd, "\n");
		list = list->next;
	}
}

t_command_list		*form_list(char *file, int size, int endianess)
{
	t_command_list	*last;
	t_command_list	*next;
	t_command_list	*list;
	int				i;

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
	return (list);
}

void				free_list(t_command_list *list)
{
	t_command_list *next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

void				disass(char *file, int fd, int size)
{
	int				endianess;
	t_command_list	*list;

	endianess = check_endianess();
	dprintf(fd, NAME_CMD_STRING);
	dprintf(fd, " \"%s\"\n", &(file[4]));
	dprintf(fd, COMMENT_CMD_STRING);
	dprintf(fd, " \"%s\"\n", &(file[12 + PROG_NAME_LENGTH]));
	list = form_list(file, size, endianess);
	print_commands_to_file(list, fd);
	free_list(list);
}
