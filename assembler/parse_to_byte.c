/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:58:13 by caking            #+#    #+#             */
/*   Updated: 2020/06/18 20:24:17 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			manage_args(t_token_list **list, t_command_list *result, t_program *prog)
{
	int			op_code = (*list)->token.op_code;
	int			count;

	*list = (*list)->next;
	count = 0;
	result->command.op_code = op_code;
	result->command.labels[0] = NULL;
	result->command.labels[1] = NULL;
	result->command.labels[2] = NULL;
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
		result->command.str_num = (*list)->token.str_num;
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
		*list = (*list)->next;
	}
	else
	{
		result->command.is_label = 0;
		if ((*list)->token.type != OPERATION)
		{
			ft_putstr("Sintaxic error\n");
			exit (0);
		}
		prog->header.prog_size += 1;
		prog->header.prog_size += op_tab[(*list)->token.op_code - 1].arg_types_code;
		result->command.str_num = (*list)->token.str_num;
		manage_args(list, result, prog);
	}
	return (result);
}

void			replace_one_label_by_value(t_command *command, int count, t_label_list *list, int bytes, int args_bytes)
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
		command->values[count] = list->label_position - bytes + args_bytes;
	else
	{
		ft_putstr("Reference to undefined label\n");
		ft_putstr(command->labels[count]);
		printf("\t%d",command->str_num);
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
		int			count_args_len = -byte_count;
		byte_count += 1 + op_tab[list->command.op_code -1].arg_types_code;
		while (count < op_tab[list->command.op_code - 1].args_num)
		{
			if (list->command.types[count] == INDIRECT_LABEL || list->command.types[count] == DIRECT_LABEL)
				replace_one_label_by_value(&list->command, count, prog->labels, byte_count, count_args_len + byte_count);
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