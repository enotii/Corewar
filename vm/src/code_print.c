/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:26:37 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/24 11:38:18 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	take_flag_v(t_cw *cw, int num, int *i)
{
	int k;

	if (num < 1)
		exit_print(cw, "-v <positive integer>\n");
	k = 0;
	while (k < 4)
	{
		cw->v_print[k++] = num % 2;
		num = num / 2;
	}
	*i += 2;
}

void	exit_print(t_cw *cw, char *str)
{
	free_cw(cw);
	ft_putstr_fd(str, 2);
	exit(0);
}

void	print_dump_code(t_cw *cw)
{
	int i;
	int k;

	k = 0;
	i = 0;
	ft_printf("%.4p : ", k);
	while (i < MEM_SIZE)
	{
		if (i % (64) == 0 && i != 0)
		{
			k++;
			ft_printf("\n");
			ft_printf("%.4p : ", k * 64);
		}
		ft_printf("%.2x ", cw->code[i]);
		i++;
	}
	ft_printf("\n");
	exit(0);
}

void	print_adv(t_cw *cw, t_carriage *tmp)
{
	int		i;

	if (cw->v_print[2] == 1 && tmp->i > 1)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ",
				tmp->i, tmp->cur, tmp->cur + tmp->i);
		i = tmp->cur;
		while (i < (tmp->cur + tmp->i))
		{
			ft_printf("%02x ",
					cw->code[i % MEM_SIZE], cw->code[i % MEM_SIZE]);
			++i;
		}
		ft_printf("\n");
	}
}
