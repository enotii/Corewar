/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:23:59 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/24 11:49:53 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** После того, как на арене были размещены исполняемые коды чемпионов,
** на начало каждого из них устанавливается каретка.**
** надо создать список для всех кареток -
** добавляем сверху сверху начинаем заполнять
** cw->carr = carr_list(cw);
*/

t_carriage	*carr_list(t_cw *cw)
{
	int			i;
	t_carriage	*carr;
	t_carriage	*carr_tmp;

	cw->n_curr = 0;
	carr = new_curr(1, cw);
	carr->cur = 0;
	i = 2;
	while (i <= cw->n)
	{
		carr_tmp = new_curr(i, cw);
		carr_tmp->cur = (i - 1) * (MEM_SIZE / cw->n);
		add_curr(&carr, carr_tmp);
		i++;
	}
	return (carr);
}

void	memset_colormap(t_cw *cw, int i)
{
	unsigned int		k;

	k = 0;
	while (k < cw->m_ch[i].prog_size)
	{
		cw->colormap[k + i * (MEM_SIZE / cw->n)] = i + 1;
		k++;
	}
}

void	map(t_cw *cw)
{
	int				i;
	unsigned char	*code_i;

	i = 0;
	while (i < cw->n)
	{
		code_i = cw->code + i * (MEM_SIZE / cw->n);
		ft_strncpy_all((code_i), cw->m_ch[i].code, cw->m_ch[i].prog_size);
		memset_colormap(cw, i);
		i++;
	}
	cw->carr = carr_list(cw);
	i = 0;
	if (cw->n)
		ft_printf("Introducing contestants...\n");
	else
		exit_print(cw, "Usage: ./corewar [-dump <N> | -n --stealth"
		"| -viz --visual | -a <champion1.cw> --on_viz_aff | -v --debug]\n");
	while (i < cw->n)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
				cw->m_ch[i].prog_size, cw->m_ch[i].prog_name,
				cw->m_ch[i].comment);
		i++;
	}
}