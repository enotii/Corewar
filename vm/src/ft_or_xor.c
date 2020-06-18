/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or_xor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 14:15:55 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/19 00:17:02 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** возможно перед чтением дир нужно двигаться на i еще
*/

void	ft_or(t_cw *cor, t_carriage *tmp)
{
	int				a1;
	int				a2;
	unsigned char	r3;
	char			*b2;
	int				f_err;

	tmp->i = 2;
	b2 = base16_2_cor(cor, tmp);
	f_err = (b2[6] == 0 && b2[7] == 0) ? 0 : 1;
	a1 = arg_4(b2, tmp, cor, &f_err);
	a2 = arg_4(b2 + 2, tmp, cor, &f_err);
	if (b2[4] == 0 && b2[5] == 1)
	{
		r3 = read_byte_1(cor->code, tmp->cur + tmp->i++);
		if ((val_reg(r3)) && !f_err)
		{
			tmp->reg[(int)r3 - 1] = a1 | a2;
			tmp->carry = (tmp->reg[(int)r3 - 1] == 0) ? 1 : 0;
			if (cor->v_print[2] == 1)
				ft_printf("P %4d | or %d %d r%d\n", tmp->num, a1, a2, r3);
		}
	}
	else
		tmp->i += 4 * (int)b2[4] - 2 * (int)b2[5];
	free(b2);
}

void	ft_xor(t_cw *cor, t_carriage *tmp)
{
	int				a1;
	int				a2;
	unsigned char	r3;
	char			*b2;
	int				f_err;

	tmp->i = 2;
	b2 = base16_2_cor(cor, tmp);
	f_err = (b2[6] == 0 && b2[7] == 0) ? 0 : 1;
	a1 = arg_4(b2, tmp, cor, &f_err);
	a2 = arg_4(b2 + 2, tmp, cor, &f_err);
	if (b2[4] == 0 && b2[5] == 1)
	{
		r3 = read_byte_1(cor->code, tmp->cur + tmp->i++);
		if ((val_reg(r3)) && !f_err)
		{
			tmp->reg[(int)r3 - 1] = a1 ^ a2;
			tmp->carry = (tmp->reg[(int)r3 - 1] == 0) ? 1 : 0;
			if (cor->v_print[2] == 1)
				ft_printf("P %4d | xor %d %d r%d\n", tmp->num, a1, a2, r3);
		}
	}
	else
		tmp->i += 4 * (int)b2[4] - 2 * (int)b2[5];
	free(b2);
}
