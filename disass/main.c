/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:43:14 by ilya              #+#    #+#             */
/*   Updated: 2020/06/20 18:16:18 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

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
		new_str = (char*)malloc(ft_strlen(content) + num + 1);
		ft_memcpy(new_str, content, ft_strlen(content));
		ft_memcpy(new_str + ft_strlen(content), buffer, num);
		new_str[ft_strlen(content) + num] = '\0';
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
	else if (op_tab[command].valid_arg_types[0] & T_REG)
		return (REGISTER);
}

t_command_list	*next_disass_command(char* file, int *i)
{
	t_command_list *ret = malloc(sizeof(t_command));
	ret->next = NULL;
	ret->command.is_label = 0;
	ret->command.op_code = (int)file[*i];
	(*i)++;
	if (op_tab[ret->command.op_code - 1].arg_types_code)
	{
		ret->command.types[0] = get_identifier(ret->command.op_code >> 6 && 0x3);
		ret->command.types[1] = get_identifier(ret->command.op_code >> 4 && 0x3);
		ret->command.types[2] = get_identifier(ret->command.op_code >> 2 && 0x3);
		(*i)++;
	}
	else
		ret->command.types[0] = get_type_by_command(ret->command.op_code - 1);
	for (int count = 0; count < op_tab[ret->command.op_code - 1].args_num; count++)
	{
		if (ret->command.types[count] == INDIRECT)
		{
			ret->command.values[count] = (int16_t*)file[*i];
			*i += IND_SIZE;
		}
		else if (ret->command.types[count] == DIRECT)
		{
			ret->command.values[count] = (int32_t*)file[*i];
			*i += DIR_SIZE;
		}
		else if (ret->command.types[count] == REGISTER)
		{
			ret->command.values[count] = (int32_t*)file[*i];
			*i += REG_SIZE;
		}
	}
	return (ret);
}

void	print_commands_to_file(t_command_list *list, int fd)
{
	while (list)
	{
		fprintf(fd, "%s ", op_tab[list->command.op_code - 1].op_name);
		for (int i = 0; i < op_tab[list->command.op_code - 1].args_num; ++i)
		{
			if (list->command.types[i] == INDIRECT)
				fprintf(fd, "%d", list->command.values[i]);
			else if (list->command.types[i] == DIRECT)
				fprintf(fd, "%c%d", DIRECT_CHAR, list->command.values[i]);
			else if (list->command.types[i] == REGISTER)
				fprintf(fd, "r%d", DIRECT_CHAR, list->command.values[i]);
			if (i != op_tab[list->command.op_code - 1].args_num - 1)
			fprintf(fd, ", ");
		}
		list = list->next;
	}
}

void	disass(char *file, int fd, int size)
{
	fprintf(fd, NAME_CMD_STRING);
	fprintf(fd, " %s\n", &file[4]);
	fprintf(fd, COMMENT_CMD_STRING);
	fprintf(fd, " %s\n", &file[12 + PROG_NAME_LENGTH]);
	t_command_list *list = NULL;
	t_command_list *last = NULL;
	int i = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH;
	while (i < size)
	{
		t_command_list	*next = next_disass_command(file, &i);
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
	int		fd = open("new_file.s", O_CREAT);
	disass(file, fd, size);
	free(file);
	 return (0);
}
