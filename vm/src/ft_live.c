/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 14:02:33 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/24 11:38:18 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** 	Если указанный в качестве аргумента операции live номер совпадает
**	 с номером игрока, то она засчитывает, что это игрок жив.
**	 Например, если значение аргумента равно -2, значит игрок с номером 2 жив.
**
** я не могу засчитать каретке которая в аргументе, что она жива
** ft_printf("A process shows that player %s is alive\n",
** cw->m_ch[i]->prog_name);
*/

void	ft_live(t_cw *cw, t_carriage *tmp)
{
	unsigned int	t_dir;
	int				i;

	i = 0;
	tmp->cycles_live = cw->live.cyc;
	cw->live.live_count++;
	t_dir = read_byte_4(cw->code, tmp->cur + 1);
	if (cw->v_print[2] == 1)
		ft_printf("P %4d | live %d\n", tmp->num, t_dir);
	while (i < cw->n)
	{
		if ((cw->m_ch[i].id + 1) == -t_dir)
		{
			cw->live.id_live = i + 1;
			if (cw->v_print[0] == 1)
				ft_printf("Player %d (%s) is said to be alive\n", -t_dir,
						cw->m_ch[i].prog_name);
		}
		i++;
	}
	tmp->i = 5;
}
