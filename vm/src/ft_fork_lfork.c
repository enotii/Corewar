/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_lfork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:53:36 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/19 00:09:09 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Операция fork делает копию каретки. И эту копию размещает
** по адресу <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
** создадим копию каретки и вставим в начало
** lfork не усекает по IDX_MOD
*/
/*
** void	printList(t_carr *tmp)
** {
** 	t_carr	*car;
**
** 	car = tmp;
** 	while(car)
** 	{
** 		ft_printf("{%d %d} --> ", car->num, car->id_par);
** 		car = car->next;
** 	}
** 	ft_printf("LLL\n");
** }
*/

t_carriage				*ft_fork(t_cw *cor, t_carriage *tmp, int l)
{
	t_carriage			*new;
	short			t_ind;
	int				k;

	new = new_curr(tmp->num, cor);
	new->carry = tmp->carry;
	new->cycles_live = tmp->cycles_live;
	k = -1;
	while (++k < REG_NUMBER)
		new->reg[k] = tmp->reg[k];
	t_ind = read_byte_2(cor->code, tmp->cur + 1);
	if (l == 0)
		new->cur = tmp->cur + idx_mod(t_ind);
	else
		new->cur = tmp->cur + t_ind;
	new->cur = mem_size(new->cur);
	add_curr(&(cor->carr), new);
	tmp->i = 3;
	if (cor->v_print[2] == 1)
		ft_printf("P %4d |%sfork %d (%d)\n", tmp->num, (l) ? " l" : " ",
			t_ind, tmp->cur + t_ind % IDX_MOD);
	return (cor->carr);
}
