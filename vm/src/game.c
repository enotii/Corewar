/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 21:30:09 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/24 11:46:32 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ПРОВЕРКА
** Текущее количество проверок» включает и проводящуюся в
** данный момент проверку.
** Мертвой считается каретка, которая выполняла операцию live cyc_to_die
** циклов назад или более.
** Также мертвой считается любая каретка, если cyc_to_die <= 0.
**
** Если количество выполненных за cyc_to_die период
** операций live больше или равно NBR_LIVE, значение cyc_to_die
** уменьшается на CYCLE_DELTA.
** Если в течение MAX_CHECKS раз проверок Cycle_to_die не уменьшался //
** то cycle_to_die уменьшается на CYCLE_DELTA
** Если же количество выполненных операций live меньше установленного лимита,
** то виртуальная машина просто запоминает, что была выполнена проверка.
** Количество операций live обнуляется после каждой
** проверки вне зависимости от ее результатов.
** check_to_die - изменяет кол-во циклов до смерти
** check_live - удаляет каретки
** cw->live->live_count - кол - во  операуий лайв
** cw->live->counter - счетчик проверок от последнего изменени cyc_to_die
*/

/*
** основная ф игры
** print_dump_code - печатает код и выходит из игры, если есть dump
** do_op - переходит к оперециям 2 из них изменяют код(st и sti),
** и одна состояние лайв
** check_live - в т.ч. меняет время до смерти и
** делает проверку(удаляет лишние каретки)
*/

static t_carriage	*check_to_die(t_cw *cw)
{
	(cw->live.counter)++;
	if (cw->live.live_count >= NBR_LIVE)
	{
		cw->live.cyc_to_die = cw->live.cyc_to_die - CYCLE_DELTA;
		if (cw->v_print[1] == 1)
			ft_printf("Cycle to die is now %d\n", cw->live.cyc_to_die);
		cw->live.counter = 0;
	}
	else if (cw->live.counter == MAX_CHECKS)
	{
		cw->live.cyc_to_die = cw->live.cyc_to_die - CYCLE_DELTA;
		cw->live.counter = 0;
		if (cw->v_print[1] == 1)
			ft_printf("Cycle to die is now %d\n", cw->live.cyc_to_die);
	}
	cw->live.live_count = 0;
	return (cw->carr);
}

static t_carriage	*check_live(t_cw *cw)
{
	t_carriage *carr;
	t_carriage *prev;

	carr = cw->carr;
	prev = NULL;
	while (carr)
	{
		if ((cw->live.cyc - carr->cycles_live) >= cw->live.cyc_to_die)
		{
			if (cw->carr == carr)
				carr = remove_head(cw, carr);
			else
				carr = remove_elem(carr, &prev, cw);
		}
		else
		{
			prev = carr;
			carr = carr->next;
		}
	}
	return (cw->carr);
}

static void		cycles_read(t_cw *cw, t_carriage *tmp)
{
	if (tmp->cycles_to == 0)
	{
		tmp->cur = mem_size(tmp->cur + tmp->i);
		tmp->prog = read_byte_1(cw->code, tmp->cur);
		tmp->cycles_to = ft_cycles_to(tmp->prog);
		tmp->i = 0;
	}
}

static	void	start_game_2(t_cw *cw, t_carriage *tmp)
{
	if (cw->carr && (cw->live.cyc == cw->nbr_cyc || cw->nbr_cyc == 0))
		print_dump_code(cw);
	tmp = cw->carr;
	cw->visual.vis ? visual(cw) : 0;
	if ((cw->live.cyc++ - cw->live.cyc_tmp) >= cw->live.cyc_to_die)
	{
		tmp = check_to_die(cw);
		cw->live.cyc_tmp = cw->live.cyc - 1;
	}
	if (cw->v_print[1] == 1)
		ft_printf("It is now cycle %d\n", cw->live.cyc);
	while (tmp)
	{
		cycles_read(cw, tmp);
		if (--tmp->cycles_to == 0)
		{
			do_op(cw, tmp);
			print_adv(cw, tmp);
		}
		tmp = tmp->next;
	}
	if ((cw->live.cyc - cw->live.cyc_tmp) >= cw->live.cyc_to_die ||
		cw->live.cyc_to_die <= 0)
		tmp = check_live(cw);
}

void			start_game(t_cw *cw)
{
	while (cw->carr)
		start_game_2(cw, NULL);
	cw->visual.vis ? stop_visual(cw) : 0;
}
