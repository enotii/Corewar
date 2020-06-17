/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdonnor <rdonnor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 13:55:32 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/17 13:57:36 by Student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** загрузке значения в регистр.
** Если тип первого аргумента это T_DIR,
** то число переданное в качестве аргумента будет воспринято «как есть».
** Записать полученное число в регистр, который был передан
** в качестве второго аргумента.
** ли в регистр записали число 0, то установить значение carry в 1
*/

int		ft_ld_write(t_cor *cor, t_carr *tmp, int i, int l)
{
	short			t_ind;
	unsigned int	t_dir;
	unsigned char	t_reg;

	if (i == 4)
	{
		t_ind = read_byte_2(cor->code, tmp->cur + 2);
		t_ind = (l == 1) ? t_ind : idx_mod(t_ind);
		t_dir = read_byte_4(cor->code, (tmp->cur + mem_size(t_ind)));
	}
	else
		t_dir = read_byte_4(cor->code, tmp->cur + 2);
	t_reg = read_byte_1(cor->code, tmp->cur + i);
	if (val_reg(t_reg))
	{
		tmp->reg[t_reg - 1] = t_dir;
		tmp->carry = (tmp->reg[t_reg - 1] == 0) ? 1 : 0;
		if (cor->v_print[2] == 1)
			ft_printf("P %4d | ld %d r%d\n", tmp->num,
				tmp->reg[t_reg - 1], t_reg);
	}
	return (1);
}

void	ft_ld(t_cor *cor, t_carr *tmp, int l)
{
	char	*b2;
	int		i;
	int		f_err;

	i = 2;
	b2 = base16_2_cor(cor, tmp);
	f_err = (b2[6] == 0 && b2[7] == 0) ? 0 : 1;
	if ((b2[0] == 1 && b2[1] == 0) || (b2[0] == 1 && b2[1] == 1))
		i += 4 * (int)b2[0] - 2 * (int)b2[1];
	else if (b2[0] == 0 && b2[1] == 1)
		i += 1;
	if (b2[2] == 0 && b2[3] == 1)
	{
		i += 1;
		if ((i == 5 || i == 7) && !f_err)
			ft_ld_write(cor, tmp, (i - 1), l);
	}
	else if ((b2[2] == 1 && b2[3] == 0) || (b2[2] == 1 && b2[3] == 1))
		i += 4 * (int)b2[2] - 2 * (int)b2[3];
	free(b2);
	tmp->i = i;
}

int		ft_lld_write(t_cor *cor, t_carr *tmp, int i)
{
	short			t_ind;
	unsigned int	t_dir;
	unsigned char	t_reg;

	t_dir = 0;
	t_ind = 0;
	if (i == 4)
	{
		t_ind = read_byte_2(cor->code, tmp->cur + 2);
		t_ind = read_byte_2(cor->code, (tmp->cur + t_ind));
	}
	else
		t_dir = read_byte_4(cor->code, tmp->cur + 2);
	t_reg = read_byte_1(cor->code, tmp->cur + i);
	if (val_reg(t_reg))
	{
		tmp->reg[t_reg - 1] = (t_ind == 0) ? (long)t_dir : t_ind;
		tmp->carry = (tmp->reg[t_reg - 1] == 0) ? 1 : 0;
	}
	if (cor->v_print[2] == 1)
		ft_printf("P %4d | lld %d r%d\n", tmp->num,
			tmp->reg[t_reg - 1], t_reg);
	return (1);
}

void	ft_lld(t_cor *cor, t_carr *tmp)
{
	char	*b2;
	int		i;

	i = 2;
	b2 = base16_2_cor(cor, tmp);
	if ((b2[0] == 1 && b2[1] == 0) || (b2[0] == 1 && b2[1] == 1))
		i += 4 * (int)b2[0] - 2 * (int)b2[1];
	else if (b2[0] == 0 && b2[1] == 1)
		i += 1;
	if (b2[2] == 0 && b2[3] == 1)
	{
		i += 1;
		if (i == 5 || i == 7)
			ft_lld_write(cor, tmp, i - 1);
	}
	else if ((b2[2] == 1 && b2[3] == 1) || (b2[2] == 1 && b2[3] == 0))
		i += 4 * (int)b2[2] - 2 * (int)b2[3];
	free(b2);
	tmp->i = i;
}
