/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:49:33 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/26 13:23:37 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			to_int(unsigned char *c)
{
	return ((c[0] << 24) | (c[1] << 16) | (c[2] << 8) | c[3]);
}

int			val_reg(unsigned char reg)
{
	return ((reg > 0 && reg <= REG_NUMBER) ? 1 : 0);
}

static void	init_live(t_cw *cw)
{
	cw->live.cyc_tmp = 0;
	cw->live.id_live = cw->n;
	cw->live.cyc = 0;
	cw->live.live_count = 0;
	cw->live.cyc_to_die = CYCLE_TO_DIE;
	cw->aff = 0;
}

static void	init_flags_cw(t_cw *cw)
{
	cw->v_print[0] = -1;
	cw->v_print[1] = -1;
	cw->v_print[2] = -1;
	cw->v_print[3] = -1;
}

int			main(int ac, char **av)
{
	static t_cw cw;

	if (ac >= 2)
	{
		init_flags_cw(&cw);
		parser(ac, av, &cw);
		map(&cw);
		init_live(&cw);
		cw.visual.vis ? init_window(&cw) : 0;
		start_game(&cw);
		if (cw.n)
			ft_printf("Contestant %d, \"%s\", has won !\n", cw.live.id_live,
				(cw.m_ch[cw.live.id_live - 1]).prog_name);
		free_cw(&cw);
	}
	else
		exit_print(&cw, "Usage: ./corewar [-dump <N> | -n --stealth"
		" | -viz --visual | -a <champion1.cor> --on_viz_aff | -v --debug]\n");
	endwin();
	return (0);
}
