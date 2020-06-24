/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:52:27 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/24 11:38:18 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_and(t_cw *cw, t_carriage *tmp)
{
	int				a1;
	int				a2;
	unsigned char	t_reg_3;
	char			*b2;
	int				f_err;

	tmp->i = 2;
	b2 = base16_2_cw(cw, tmp);
	f_err = 0;
	a1 = arg_4(b2, tmp, cw, &f_err);
	a2 = arg_4(b2 + 2, tmp, cw, &f_err);
	if (b2[4] == 0 && b2[5] == 1)
	{
		t_reg_3 = read_byte_1(cw->code, tmp->cur + tmp->i++);
		if ((val_reg(t_reg_3)) && !f_err)
		{
			tmp->reg[t_reg_3 - 1] = a1 & a2;
			tmp->carry = (tmp->reg[t_reg_3 - 1] == 0) ? 1 : 0;
		}
		if (cw->v_print[2] == 1)
			ft_printf("P %4d | and %d %d r%d\n", tmp->num, a1, a2, t_reg_3);
	}
	else
		tmp->i += 4 * b2[4] - 2 * b2[5];
	free(b2);
}
