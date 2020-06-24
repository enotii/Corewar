/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:40:59 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/24 11:46:54 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_carriage	*new_curr(int id_par, t_cw *cw)
{
	t_carriage	*new;
	int		i;

	new = NULL;
	new = (t_carriage *)ft_memalloc(sizeof(t_carriage));
	if (!new)
		return (NULL);
	new->id_par = id_par;
	new->i = 0;
	new->carry = 0;
	new->cycles_to = 0;
	new->num = ++cw->n_curr;
	i = 0;
	new->reg[i] = -id_par;
	while (++i < REG_NUMBER)
		new->reg[i] = 0;
	new->next = NULL;
	return (new);
}

void	add_curr(t_carriage **all_carr, t_carriage *new)
{
	if (!all_carr || !*all_carr)
		return ;
	new->next = *all_carr;
	*all_carr = new;
}

int		len_curr(t_carriage *list)
{
	int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_carriage	*remove_head(t_cw *cw, t_carriage *curr)
{
	cw->carr = curr->next;
	if (cw->v_print[3] == 1)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				curr->num, cw->live.cyc - curr->cycles_live,
				cw->live.cyc_to_die);
	free(curr);
	curr = cw->carr;
	return (curr);
}

t_carriage	*remove_elem(t_carriage *curr, t_carriage **prev, t_cw *cw)
{
	int		temp_id;
	int		temp_cycles_live;

	temp_id = curr->num;
	temp_cycles_live = curr->cycles_live;
	curr = curr->next;
	free((*prev)->next);
	(*prev)->next = curr;
	if (cw->v_print[3] == 1)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", temp_id,
				cw->live.cyc - temp_cycles_live, cw->live.cyc_to_die);
	return (curr);
}