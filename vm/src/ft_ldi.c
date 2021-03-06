/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:58:17 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/24 11:38:18 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		ldi_take_argc(unsigned char t_reg, int *k,
							int *f_err, t_carriage *tmp)
{
	if (val_reg(t_reg))
		*k += tmp->reg[(int)t_reg - 1];
	else
		*f_err = 1;
}

static int		len_k(t_cw *cw, t_carriage *tmp, char *b2, int *f_err)
{
	int				k;
	unsigned char	t_reg;

	cw->addr1 = arg_2(b2, tmp, cw, f_err);
	k = cw->addr1;
	if (b2[2] == 0 && b2[3] == 1)
	{
		t_reg = read_byte_1(cw->code, (tmp->cur + tmp->i++));
		cw->addr2 = t_reg;
		ldi_take_argc(t_reg, &k, f_err, tmp);
	}
	else if ((b2[2] == 1 && b2[3] == 0))
	{
		cw->addr2 = read_byte_2(cw->code, tmp->cur + tmp->i);
		k += cw->addr2;
		tmp->i += 2;
	}
	else
	{
		tmp->i += 2 * b2[2];
		*f_err = 1;
	}
	return (k);
}

static void		print_ldi(t_cw *cw, t_carriage *tmp,
					unsigned char t_reg, int k1)
{
	if (cw->v_print[2] == 1)
	{
		ft_printf("P %4d | %s %d %d r%d\n", tmp->num,
				(tmp->prog == 14) ? "lldi" : "ldi",
						cw->addr1, cw->addr2, t_reg);
		ft_printf("       | -> load from %d + %d = %d (with pc%s%d)\n", \
			cw->addr1, cw->addr2, k1, (tmp->prog == 14) ? " " : " and mod ",
				tmp->cur + ((cw->addr1 + cw->addr2) % IDX_MOD));
	}
}

static void		ldi_get_argc(int k, t_carriage *tmp,
				unsigned char t_reg, t_cw *cw)
{
	k = mem_size(tmp->prog == 10 ? k % IDX_MOD : k);
	tmp->reg[(int)t_reg - 1] =
			read_byte_4(cw->code, mem_size(tmp->cur + k));
	if (tmp->prog == 14)
		tmp->carry = (tmp->reg[t_reg - 1] == 0) ? 1 : 0;
}

void			ft_ldi(t_cw *cw, t_carriage *tmp)
{
	unsigned char	t_reg;
	char			*b2;
	int				f_err;
	int				k;
	int				k1;

	tmp->i = 2;
	b2 = base16_2_cw(cw, tmp);
	f_err = (b2[6] == 0 && b2[7] == 0) ? 0 : 1;
	k = len_k(cw, tmp, b2, &f_err);
	k1 = k;
	if (b2[4] == 0 && b2[5] == 1)
	{
		t_reg = read_byte_1(cw->code, tmp->cur + tmp->i++);
		if (f_err == 0 && (val_reg(t_reg)))
			ldi_get_argc(k, tmp, t_reg, cw);
		print_ldi(cw, tmp, t_reg, k1);
	}
	else
		tmp->i += 2 * b2[4];
	free(b2);
}
