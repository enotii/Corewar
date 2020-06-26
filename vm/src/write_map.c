/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 00:32:39 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/26 14:02:55 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		mem(int x)
{
	return (((x) % (M)) < 0 ?
		(((x) % (M)) + (M)) : ((x) % (M)));
}

void	panel_help(t_cw *cw, WINDOW *main_win, int i, int line)
{
	int	col;
	int	j;

	col = 2;
	j = -1;
	while (++j < 64)
	{
		if (cw->bold[i * 64 + j] && (cw->bold[i * 64 + j] -= 1))
			wattron(main_win, A_BOLD);
		wattron(main_win, COLOR_PAIR(cw->colormap[i * 64 + j]));
		mvwprintw(main_win, line, col, "%.2x ", cw->code[i * 64 + j]);
		wattroff(main_win, COLOR_PAIR(cw->colormap[i * 64 + j]));
		if (cw->bold[i * 64 + j])
			wattroff(main_win, A_BOLD);
		col += 3;
	}
}

void	write_map_color(t_cw *cw, int pos, int len, t_carriage *carg)
{
	int	i;

	if (cw->visual.vis)
	{
		i = -1;
		while (++i < len)
		{
			cw->colormap[mem(pos + i)] = (unsigned char)(carg->id_par);
			cw->bold[mem(pos + i)] = 70;
		}
	}
}

void	stop_visual(t_cw *cw)
{
	if (cw->visual.vis)
	{
		end_game(cw);
		while (1)
			if (getch() == 32)
			{
				delwin(cw->visual.main_win);
				delwin(cw->visual.side_win);
				endwin();
				exit(1);
			}
	}
}

void	end_game(t_cw *cw)
{
	wattron(cw->visual.side_win, COLOR_PAIR(4));
	mvwprintw(cw->visual.side_win, 1, 2, "** END OF THE GAME **");
	wattroff(cw->visual.side_win, COLOR_PAIR(4));
	wattron(cw->visual.side_win, COLOR_PAIR(1));
	mvwprintw(cw->visual.side_win, 32, 2, "Winner ->[%d] %s ",
			cw->live.id_live, (cw->m_ch[cw->live.id_live - 1]).prog_name);
	wattroff(cw->visual.side_win, COLOR_PAIR(1));
	wrefresh(cw->visual.side_win);
}
