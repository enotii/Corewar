/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 14:02:33 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/19 00:16:07 by sscottie         ###   ########.fr       */
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
** cor->m_ch[i]->prog_name);
*/

void	ft_live(t_cw *cor, t_carriage *tmp)
{
	unsigned int	t_dir;
	int				i;

	i = 0;
	tmp->cycles_live = cor->live.cyc;
	cor->live.live_count++;
	t_dir = read_byte_4(cor->code, tmp->cur + 1);
	if (cor->v_print[2] == 1)
		ft_printf("P %4d | live %d\n", tmp->num, t_dir);
	while (i < cor->n)
	{
		if ((cor->ch[i].id + 1) == -t_dir)
		{
			cor->live.id_live = i + 1;
			if (cor->v_print[0] == 1)
				ft_printf("Player %d (%s) is said to be alive\n", -t_dir,
						cor->ch[i].prog_name);
		}
		i++;
	}
	tmp->i = 5;
}
