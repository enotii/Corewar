/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdonnor <rdonnor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:52:27 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/17 13:52:56 by Student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_and(t_cor *cor, t_carr *tmp)
{
	int				a1;
	int				a2;
	unsigned char	t_reg_3;
	char			*b2;
	int				f_err;

	tmp->i = 2;
	b2 = base16_2_cor(cor, tmp);
	f_err = 0;
	a1 = arg_4(b2, tmp, cor, &f_err);
	a2 = arg_4(b2 + 2, tmp, cor, &f_err);
	if (b2[4] == 0 && b2[5] == 1)
	{
		t_reg_3 = read_byte_1(cor->code, tmp->cur + tmp->i++);
		if ((val_reg(t_reg_3)) && !f_err)
		{
			tmp->reg[t_reg_3 - 1] = a1 & a2;
			tmp->carry = (tmp->reg[t_reg_3 - 1] == 0) ? 1 : 0;
		}
		if (cor->v_print[2] == 1)
			ft_printf("P %4d | and %d %d r%d\n", tmp->num, a1, a2, t_reg_3);
	}
	else
		tmp->i += 4 * b2[4] - 2 * b2[5];
	free(b2);
}
