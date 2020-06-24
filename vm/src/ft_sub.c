/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 14:19:56 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/24 11:38:18 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_sub_1(t_cw *cw, t_carriage *tmp)
{
	unsigned char	t_reg;
	unsigned char	t_reg_2;
	unsigned char	t_reg_3;

	t_reg = read_byte_1(cw->code, tmp->cur + 2);
	t_reg_2 = read_byte_1(cw->code, tmp->cur + 3);
	t_reg_3 = read_byte_1(cw->code, tmp->cur + 4);
	if (val_reg(t_reg) && val_reg(t_reg_2) && val_reg(t_reg_3))
	{
		tmp->reg[t_reg_3 - 1] = tmp->reg[t_reg - 1] -
									tmp->reg[t_reg_2 - 1];
		tmp->carry = (tmp->reg[(int)t_reg_3 - 1] == 0) ? 1 : 0;
		if (cw->v_print[2] == 1)
			ft_printf("P %4d | sub r%d r%d r%d\n", tmp->num,
				t_reg, t_reg_2, t_reg_3);
	}
}

void		ft_sub(t_cw *cw, t_carriage *tmp)
{
	char			*b2;
	int				i;
	int				f_err;

	i = 2;
	b2 = base16_2_cw(cw, tmp);
	f_err = 0;
	if (b2[0] == 0 && b2[1] == 1)
		i += 1;
	else
		i += 4 * (int)b2[0] - 2 * (int)b2[1];
	if (b2[2] == 0 && b2[3] == 1)
		i += 1;
	else
		i += 4 * (int)b2[2] - 2 * (int)b2[3];
	if (b2[4] == 0 && b2[5] == 1)
		i += 1;
	else
		i += 4 * (int)b2[4] - 2 * (int)b2[5];
	if (i == 5 && !f_err)
		ft_sub_1(cw, tmp);
	free(b2);
	tmp->i = i;
}
