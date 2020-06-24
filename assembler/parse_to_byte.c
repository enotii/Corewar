/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 19:58:13 by caking            #+#    #+#             */
/*   Updated: 2020/06/23 22:12:09 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void			manage_norm(int op_code, t_token_list **list, int count)
{
	if ((!(g_op_tab[op_code - 1].valid_arg_types[count] & T_REG)
	&& (*list)->token.type == REGISTER)
	|| (!(g_op_tab[op_code - 1].valid_arg_types[count] & T_IND)
	&& ((*list)->token.type == INDIRECT ||
	(*list)->token.type == INDIRECT_LABEL))
	|| (!(g_op_tab[op_code - 1].valid_arg_types[count] & T_DIR)
	&& ((*list)->token.type == DIRECT ||
	(*list)->token.type == DIRECT_LABEL)))
	{
		ft_putstr("Wrong argument\n");
		exit(0);
	}
}

void			manage_arg(t_token_list **list,
int count, t_command_list *result)
{
	if ((*list)->token.type == REGISTER)
		result->command.values[count] = (*list)->token.register_num;
	else if ((*list)->token.type == INDIRECT)
		result->command.values[count] = (*list)->token.indirect;
	else if ((*list)->token.type == DIRECT)
		result->command.values[count] = (*list)->token.direct;
	else if ((*list)->token.type == DIRECT_LABEL)
		result->command.labels[count] =
		ft_strdup((*list)->token.direct_label);
	else if ((*list)->token.type == INDIRECT_LABEL)
		result->command.labels[count] =
		ft_strdup((*list)->token.indirect_label);
}

void			manage_norm2(t_token_list **list, t_program *prog, int op_code)
{
	if ((*list)->token.type == REGISTER)
		prog->header.prog_size += 1;
	else if ((*list)->token.type == INDIRECT
	|| (*list)->token.type == INDIRECT_LABEL)
		prog->header.prog_size += 2;
	else if ((*list)->token.type == DIRECT
	|| (*list)->token.type == DIRECT_LABEL)
		prog->header.prog_size += g_op_tab[op_code - 1].t_dir_size ? 2 : 4;
	*list = (*list)->next;
}

void			manage_norm3(int count, int op_code, t_token_list **list)
{
	if (count + 1 != g_op_tab[op_code - 1].args_num)
	{
		if (!(*list) || (*list)->token.type != SEPARATOR)
		{
			ft_putstr("No separator\n");
			exit(0);
		}
		*list = (*list)->next;
	}
}

void			manage_args(t_token_list **list, t_command_list *result,
t_program *prog)
{
	int			op_code;
	int			count;

	op_code = (*list)->token.op_code;
	*list = (*list)->next;
	count = 0;
	result->command.op_code = op_code;
	result->command.labels[0] = NULL;
	result->command.labels[1] = NULL;
	result->command.labels[2] = NULL;
	while (count < g_op_tab[op_code - 1].args_num)
	{
		manage_norm(op_code, list, count);
		result->command.types[count] = (*list)->token.type;
		manage_arg(list, count, result);
		manage_norm2(list, prog, op_code);
		manage_norm3(count, op_code, list);
		count++;
	}
}
