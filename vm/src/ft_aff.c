/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 13:50:12 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/19 00:07:00 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** 4 * (int)b2[0] - 2 * (int)b2[1];
** если t_dir 10 4*1 - 2*0 = 4
** если t_ind 11 4*1 - 2*2 = 2
** если 00 = 0
** if (VAL_REG(t_reg))
** ft_putchar((char)tmp->reg[(int)t_reg]);
** ft_putchar('+');
*/

void	set_aff(t_cw *cor, int *i)
{
	(*i)++;
	cor->aff = 1;
}

void	ft_aff(t_cw *cor, t_carriage *tmp)
{
	char					*b2;
	int						i;
	unsigned char			c_1;
	unsigned char			val;

	i = 2;
	b2 = base16_2_cor(cor, tmp);
	if (b2[0] == 0 && b2[1] == 1)
	{
		c_1 = read_byte_1(cor->code, (tmp->cur + i++));
		val = tmp->reg[(int)c_1 - 1];
		if (cor->v_print[2] == 1 && cor->aff != 1)
			ft_printf("Aff: %c\n", val);
	}
	else
		i = i + 4 * (int)b2[0] - 2 * (int)b2[1];
	tmp->i = i;
	free(b2);
}
