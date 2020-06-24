/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 10:20:57 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/24 11:38:18 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				ft_zjmp(t_cw *cw, t_carriage *tmp)
{
	short	t_ind;
	short	a;

	t_ind = read_byte_2(cw->code, tmp->cur + 1);
	a = idx_mod(t_ind);
	if (tmp->carry == 1)
	{
		tmp->cur = mem_size(tmp->cur + a);
		tmp->i = 0;
		if (cw->v_print[2] == 1)
			ft_printf("P %4d | zjmp %d OK\n", tmp->num, t_ind);
	}
	else
		tmp->i = 3;
	if ((cw->v_print[2] == 1) && !(tmp->carry))
		ft_printf("P %4d | zjmp %d FAILED\n", tmp->num, t_ind);
}
