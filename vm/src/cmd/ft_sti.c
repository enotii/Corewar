/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdonnor <rdonnor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:18:52 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/17 14:19:30 by Student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** копировать в зависимости от положения
** по модулю MEM_SIZE
** копирует 4 байта
** dst - куда
** src - откуда
** d_s - куда начинать вставлять
** s_s - откуда
*/

void	copy_p(void *dst, const void *src, int d_s, int s_s)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	d_s = mem_size(d_s);
	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	i = 0;
	while (i < 4)
	{
		str1[(i + d_s) % MEM_SIZE] = (char)str2[(i + s_s) % MEM_SIZE];
		i++;
	}
}

/*
** Эта операция записывает значение из регистра,
** который был передан как первый параметр.
** А вот куда данная операция его записывает, зависит от типа второго аргумента:
** Аргумент #2 — T_REG
** Если второй аргумент соответствует типу T_REG,
** то значение записывается в регистр.
** Например, в данном случае значение из регистра номер
** 7 записывается в регистр с номером 11:
** 			st    r7, r11
** Аргумент #2 — T_IND
** Как мы помним аргументы типа T_IND это об относительных адресах.
** Поэтому в данном случае порядок работы операции st такой:
** Усечь значение второго аргумента по модулю IDX_MOD.
** Определить адрес — текущая позиция + <ВТОРОЙ_АРГУМЕНТ> % IDX_MOD
** Записать значение из регистра, который был передан в качестве первого
** аргумента, в память по полученному адресу.
*/

void	ft_st_write_2(unsigned char t_reg, t_cor *cor, t_carr *tmp)
{
	unsigned char	t_reg_2;

	t_reg_2 = read_byte_1(cor->code, tmp->cur + 3);
	if (val_reg(t_reg_2))
		tmp->reg[t_reg_2 - 1] = tmp->reg[t_reg - 1];
	if (cor->v_print[2] == 1)
		ft_printf("P %4d | st r%d %d\n", tmp->num,
					t_reg, t_reg_2 % IDX_MOD);
}

void	ft_st_write(t_cor *cor, t_carr *tmp, int b2_2)
{
	unsigned char	*p;
	short			t_ind;
	unsigned char	t_reg;

	t_reg = read_byte_1(cor->code, tmp->cur + 2);
	if (val_reg(t_reg))
	{
		if (b2_2 == 1)
		{
			t_ind = read_byte_2(cor->code, tmp->cur + 3);
			if (cor->v_print[2] == 1)
				ft_printf("P %4d | st r%d %d\n", tmp->num, t_reg, t_ind);
			t_ind = idx_mod(t_ind);
			t_ind = mem_size(tmp->cur + t_ind);
			p = inttobyte(tmp->reg[t_reg - 1]);
			copy_p(cor->code, p, t_ind, 0);
			free(p);
		}
		else
			ft_st_write_2(t_reg, cor, tmp);
	}
}

void	ft_st(t_cor *cor, t_carr *tmp)
{
	char	*b2;
	int		i;

	i = 2;
	b2 = base16_2_cor(cor, tmp);
	if (b2[0] == 0 && b2[1] == 1)
		i += 1;
	else if ((b2[0] == 1 && b2[1] == 0) || (b2[0] == 1 && b2[1] == 1))
		i += 4 * (int)b2[0] - 2 * (int)b2[1];
	if ((b2[2] == 0 && b2[3] == 1) || (b2[2] == 1 && b2[3] == 1))
	{
		if (i == 3)
			ft_st_write(cor, tmp, b2[2]);
		i += (b2[2] == 0) ? 1 : 2;
	}
	else if (b2[2] == 1 && b2[3] == 0)
		i += 4;
	tmp->i = i;
	free(b2);
}
