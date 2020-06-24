/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:18:52 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/24 11:38:18 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** 1. тут дир по 2 байта
** Эта операция записывает значение регистра,
** переданного в качестве первого параметра,
** по адресу — текущая позиция +
** (<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ТРЕТЕГО_АРГУМЕНТА>) % IDX_MOD.
** t_reg - куда записывает
** Размер T_DIR = 2
** i = 2 - учитывает что прочитали программу и код параметров
** l - на сколько надо двигаться
** t_dir на 2 байта
**
**
** если IND мы считываем 4 байта по ссылке, а если дир то 2
**
** убрать один рег - сначала проверить последний а потом первый уже оставлять
*/

static void		write_sti(t_cw *cw, t_carriage *tmp,
				unsigned char t_reg, int *l_2)
{
	unsigned char	*p;

	p = inttobyte(tmp->reg[t_reg - 1], cw);
	write_map_color(cw, l_2[2], 4, tmp);
	copy_p(cw->code, p, l_2[2], 0);
	free(p);
	if (cw->v_print[2] == 1)
	{
		ft_printf("P %4d | sti r%d %d %d\n",
		tmp->num, t_reg, l_2[0], l_2[1], l_2[2]);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			l_2[0], l_2[1], l_2[0] + l_2[1],
			tmp->cur + ((l_2[0] + l_2[1]) % IDX_MOD));
	}
}

static int		len_l_2(t_cw *cw, t_carriage *tmp, char *b2, int *l_2)
{
	unsigned char	t_reg_2;
	int				f_err;

	f_err = 0;
	t_reg_2 = read_byte_1(cw->code, tmp->cur + tmp->i++);
	if (b2[4] == 0 && b2[5] == 1 && !(val_reg(t_reg_2)))
		f_err = 1;
	if (val_reg(t_reg_2))
	{
		l_2[2] = l_2[2] + (int)tmp->reg[t_reg_2 - 1];
		l_2[0] = l_2[2];
	}
	return (f_err);
}

static int		*len_l(t_cw *cw, t_carriage *tmp, char *b2, int *f_err)
{
	int				*l_2;

	if (!(l_2 = (int*)ft_memalloc(sizeof(int) * 3)))
		exit(-1);
	l_2[2] = arg_2(b2 + 2, tmp, cw, f_err);
	l_2[0] = l_2[2];
	if (b2[4] == 0 && b2[5] == 1)
		*f_err = (len_l_2(cw, tmp, b2, l_2) == 1) ? 1 : *f_err;
	else if (b2[4] == 1 && b2[5] == 0)
	{
		l_2[1] = read_byte_2(cw->code, tmp->cur + tmp->i);
		l_2[2] += l_2[1];
		tmp->i += 2;
	}
	else
	{
		tmp->i += 2 * b2[4];
		*f_err = 1;
	}
	return (l_2);
}

void			ft_sti(t_cw *cw, t_carriage *tmp)
{
	unsigned char	t_reg;
	int				f_err;
	char			*b2;
	int				*l_2;

	tmp->i = 2;
	b2 = base16_2_cw(cw, tmp);
	f_err = 0;
	if (b2[0] == 0 && b2[1] == 1)
		t_reg = read_byte_1(cw->code, tmp->cur + tmp->i++);
	else
	{
		f_err = 1;
		if ((b2[0] == 1 && b2[1] == 1) || (b2[0] == 1 && b2[1] == 0))
			tmp->i += 2;
	}
	l_2 = len_l(cw, tmp, b2, &f_err);
	l_2[2] = mem_size(tmp->cur + l_2[2] % IDX_MOD);
	if (!f_err && val_reg(t_reg))
		write_sti(cw, tmp, t_reg, l_2);
	free(b2);
	free(l_2);
}
