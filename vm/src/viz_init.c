/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:17:20 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/26 15:57:44 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	create_field(t_cw *cw)
{
	cw->visual.main_win = create_newwin(65, 195, 1, 1);
	cw->visual.side_win = create_newwin(65, 56, 1, 196);
	nodelay(cw->visual.main_win, 1);
	nodelay(cw->visual.side_win, 1);
	render(cw);
}

void	render(t_cw *cw)
{
	curs_set(0);
	usleep(cw->visual.delay);
	side_panel(cw->visual.side_win, cw);
	main_panel(cw->visual.main_win, cw);
	box(cw->visual.side_win, 0, 0);
	box(cw->visual.main_win, 0, 0);
	wrefresh(cw->visual.main_win);
	wrefresh(cw->visual.side_win);
}

void	init_window(t_cw *cw)
{
	initscr();
	cw->visual.delay = DELAY;
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	create_field(cw);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_BLACK, COLOR_RED);
	init_pair(13, COLOR_BLACK, COLOR_BLUE);
	init_pair(14, COLOR_BLACK, COLOR_CYAN);
	refresh();
}

int		graph_cycle(t_cw *cw)
{
	int		ch;

	ch = getch();
	if (ch == 27)
		return (1);
	if (ch == ' ')
	{
		cw->visual.pause++;
		cw->visual.pause %= 2;
	}
	else if (ch == '+' && cw->visual.delay <= 50000)
		cw->visual.delay += 1000;
	else if (ch == '-' && cw->visual.delay > 1000)
		cw->visual.delay -= 1000;
	else if (ch == 'w')
	{
		cw->visual.vis = 0;
		start_game(cw);
		cw->visual.vis = 1;
		render(cw);
		stop_visual(cw);
	}
	return (0);
}

void	visual(t_cw *cw)
{
	render(cw);
	graph_cycle(cw);
	while (cw->visual.pause == 0)
	{
		wattron(cw->visual.side_win, COLOR_PAIR(2));
		mvwprintw(cw->visual.side_win, 1, 2, "** PAUSED  **");
		wattroff(cw->visual.side_win, COLOR_PAIR(2));
		mvwprintw(cw->visual.side_win, 23, 2, "DELTA_TIME_PRINT : %d ",
				cw->visual.delay);
		wrefresh(cw->visual.side_win);
		if (graph_cycle(cw) == 1)
		{
			delwin(cw->visual.main_win);
			delwin(cw->visual.side_win);
			free_cw(cw);
			endwin();
			exit(1);
		}
	}
}
