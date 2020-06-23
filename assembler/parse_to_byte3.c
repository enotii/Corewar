/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_byte3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 22:11:45 by caking            #+#    #+#             */
/*   Updated: 2020/06/23 22:14:05 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			get_next_cmd_norm(t_command_list *result, t_token_list **list,
t_program *prog, t_label_list **last_label)
{
	t_label_list	*next;

	result->command.is_label = 1;
	result->command.str_num = (*list)->token.str_num;
	next = malloc(sizeof(t_label_list));
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

t_command_list	*get_next_command(t_token_list **list,
t_program *prog, t_label_list **last_label)
{
	t_command_list	*result;

	result = malloc(sizeof(t_command_list));
	if ((*list)->token.type == LABEL)
		get_next_cmd_norm(result, list, prog, last_label);
	else
	{
		result->command.is_label = 0;
		if ((*list)->token.type != OPERATION)
		{
			ft_putstr("Sintaxic error\n");
			exit(0);
		}
		prog->header.prog_size += 1;
		prog->header.prog_size += g_op_tab[(*list)->token.op_code
		- 1].arg_types_code;
		result->command.str_num = (*list)->token.str_num;
		manage_args(list, result, prog);
	}
	return (result);
}

void			rpl_one(t_command *command,
int count, t_label_list *list, int bytes)
{
	int found;

	found = 0;
	while (list)
	{
		if (!ft_strcmp(list->label_name, command->labels[count]))
		{
			found = 1;
			break ;
		}
		list = list->next;
	}
	if (found)
		command->values[count] = list->label_position + bytes;
	else
	{
		ft_putstr("Reference to undefined label\n");
		ft_putstr(command->labels[count]);
		printf("\t%d", command->str_num);
		exit(0);
	}
}

void			replace_labels_norm(int count, t_command_list *list,
t_program *prog, int *byte_count)
{
	if (list->command.types[count] == REGISTER)
		*byte_count += 1;
	else if (list->command.types[count] == INDIRECT ||
	list->command.types[count] == INDIRECT_LABEL)
		*byte_count += 2;
	else if (list->command.types[count] == DIRECT ||
	list->command.types[count] == DIRECT_LABEL)
		*byte_count += g_op_tab[list->command.op_code - 1].
		t_dir_size ? 2 : 4;
}

void			replace_labels_with_values(t_program *prog)
{
	t_command_list	*list;
	int				bc;
	int				count;
	int				cnt;

	bc = 0;
	list = prog->list;
	while (list)
	{
		if (!list->command.is_label)
		{
			count = 0;
			cnt = -bc;
			bc += 1 + g_op_tab[list->command.op_code - 1].arg_types_code;
			while (count < g_op_tab[list->command.op_code - 1].args_num)
			{
				if (list->command.types[count] == INDIRECT_LABEL ||
				list->command.types[count] == DIRECT_LABEL)
					rpl_one(&list->command, count, prog->labels, cnt);
				replace_labels_norm(count, list, prog, &bc);
				count++;
			}
		}
		list = list->next;
	}
}
