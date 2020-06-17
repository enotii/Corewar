/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdonnor <rdonnor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 10:20:57 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/17 14:21:09 by rdonnor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				ft_zjmp(t_cor *cor, t_carr *tmp)
{
	short	t_ind;
	short	a;

	t_ind = read_byte_2(cor->code, tmp->cur + 1);
	a = idx_mod(t_ind);
	if (tmp->carry == 1)
	{
		tmp->cur = mem_size(tmp->cur + a);
		tmp->i = 0;
		if (cor->v_print[2] == 1)
			ft_printf("P %4d | zjmp %d OK\n", tmp->num, t_ind);
	}
	else
		tmp->i = 3;
	if ((cor->v_print[2] == 1) && !(tmp->carry))
		ft_printf("P %4d | zjmp %d FAILED\n", tmp->num, t_ind);
}
