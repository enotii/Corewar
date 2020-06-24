/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 22:43:14 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/24 11:46:41 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	do_op_two(t_cw *cw, t_carriage *tmp)
{
	if (tmp->prog == 1)
		ft_live(cw, tmp);
	else if (tmp->prog == 2)
		ft_ld(cw, tmp, 0);
	else if (tmp->prog == 3)
		ft_st(cw, tmp);
	else if (tmp->prog == 4)
		ft_add(cw, tmp);
	else if (tmp->prog == 5)
		ft_sub(cw, tmp);
	else if (tmp->prog == 6)
		ft_and(cw, tmp);
	else if (tmp->prog == 7)
		ft_or(cw, tmp);
	else if (tmp->prog == 8)
		ft_xor(cw, tmp);
	else if (tmp->prog == 9)
		ft_zjmp(cw, tmp);
	else if (tmp->prog == 10)
		ft_ldi(cw, tmp);
	else if (tmp->prog == 11)
		ft_sti(cw, tmp);
	else if (tmp->prog == 12)
		ft_fork(cw, tmp, 0);
}

void	do_op(t_cw *cw, t_carriage *tmp)
{
	if (tmp->prog > 0 && tmp->prog < 13)
		do_op_two(cw, tmp);
	else if (tmp->prog == 13)
		ft_lld(cw, tmp);
	else if (tmp->prog == 14)
		ft_ldi(cw, tmp);
	else if (tmp->prog == 15)
		ft_fork(cw, tmp, 1);
	else if (tmp->prog == 16)
		ft_aff(cw, tmp);
	else
		tmp->i = 1;
}

int		ft_cycles_to(char p)
{
	int	cycles;

	cycles = 1;
	if (p == 1 || p == 4 || p == 5 || p == 13)
		cycles = 10;
	else if (p == 2 || p == 3)
		cycles = 5;
	else if (p == 6 || p == 7 || p == 8)
		cycles = 6;
	else if (p == 9)
		cycles = 20;
	else if (p == 10 || p == 11)
		cycles = 25;
	else if (p == 12)
		cycles = 800;
	else if (p == 14)
		cycles = 50;
	else if (p == 15)
		cycles = 1000;
	else if (p == 16)
		cycles = 2;
	return (cycles);
}
