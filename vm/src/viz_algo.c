/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:17:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/26 16:08:34 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

WINDOW	*create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);
	wrefresh(local_win);
	return (local_win);
}

int		players(WINDOW *side_win, int line, t_cw *cw)
{
	int			i;
	int			j;
	t_carriage	*tmp;

	i = -1;
	while (++i < cw->n && !(j = 0))
	{
		wattron(side_win, COLOR_PAIR(cw->m_ch[i].id + 1));
		mvwprintw(side_win, line++, 2, "Player %d : %s \n",
				cw->m_ch[i].id + 1, cw->m_ch[i].prog_name);
		wattroff(side_win, COLOR_PAIR(cw->m_ch[i].id + 1));
		tmp = cw->carr;
		while (tmp)
		{
			tmp->id_par == i + 1 ? ++j : 0;
			tmp = tmp->next;
		}
		mvwprintw(side_win, line++, 4, "Lives in current period :\t\t%d    ",
				j);
		line++;
	}
	return (line);
}

void	side_panel(WINDOW *side_win, t_cw *cw)
{
	int line;

	line = 7;
	if (cw->visual.pause == 0)
	{
		wattron(side_win, COLOR_PAIR(2));
		mvwprintw(side_win, 1, 2, "** PAUSED **");
		wattroff(side_win, COLOR_PAIR(2));
	}
	else
	{
		wattron(side_win, COLOR_PAIR(1));
		mvwprintw(side_win, 1, 2, "** RUNNING **");
		wattroff(side_win, COLOR_PAIR(1));
	}
	mvwprintw(side_win, 3, 2, "Cycle : %d ", cw->live.cyc);
	mvwprintw(side_win, 5, 2, "Processes : %d ", cw->n);
	line = players(side_win, line, cw);
	mvwprintw(side_win, line, 2, "CYCLE_TO_DIE : %d ", cw->live.cyc_to_die);
	mvwprintw(side_win, line + 2, 2, "CYCLE_DELTA : %d ", CYCLE_DELTA);
	mvwprintw(side_win, 23, 2, "DELTA_TIME_PRINT : %d ",
	cw->visual.delay);
	mvwprintw(side_win, 60, 2,
		"USAGE:\n  PAUSE = SPACE\n  SPEED: '-' / '+'\n  FINAL: 'w'");
}

void	paint_carg(t_cw *cw)
{
	t_carriage	*carg;
	int			color;

	carg = cw->carr;
	while (carg)
	{
		carg->cur = mem(carg->cur);
		color = cw->colormap[carg->cur] + 10;
		wattron(cw->visual.main_win, COLOR_PAIR(color));
		mvwprintw(cw->visual.main_win, carg->cur / 64 + 1,
				2 + (carg->cur % 64) * 3, "%.2x", cw->code[carg->cur]);
		wattroff(cw->visual.main_win, COLOR_PAIR(color));
		carg = carg->next;
	}
	wrefresh(cw->visual.main_win);
}

void	main_panel(WINDOW *main_win, t_cw *cw)
{
	int		i;
	int		line;

	line = 1;
	i = -1;
	while (++i < 64)
	{
		panel_help(cw, main_win, i, line);
		line++;
	}
	paint_carg(cw);
}
