/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:26:37 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/18 22:48:19 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_dump_code(t_cw *cor)
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
		ft_printf("%.2x ", cor->code[i]);
		i++;
	}
	ft_printf("\n");
	exit(0);
}

void	print_adv(t_cw *cor, t_carriage *tmp)
{
	int		i;

	if (cor->v_print[2] == 1 && tmp->i > 1)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ",
				tmp->i, tmp->cur, tmp->cur + tmp->i);
		i = tmp->cur;
		while (i < (tmp->cur + tmp->i))
		{
			ft_printf("%02x ",
					cor->code[i % MEM_SIZE], cor->code[i % MEM_SIZE]);
			++i;
		}
		ft_printf("\n");
	}
}