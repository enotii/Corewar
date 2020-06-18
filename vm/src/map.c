/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:23:59 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/18 23:50:59 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** После того, как на арене были размещены исполняемые коды чемпионов,
** на начало каждого из них устанавливается каретка.**
** надо создать список для всех кареток -
** добавляем сверху сверху начинаем заполнять
** cor->carr = carr_list(cor);
*/

t_carriage	*carr_list(t_cw *cor)
{
	int		i;
	t_carriage	*carr;
	t_carriage	*carr_tmp;

	cor->n_curr  = 0;
	carr = new_curr(1, cor);
	carr->cur = 0;
	i = 2;
	while (i <= cor->n)
	{
		carr_tmp = new_curr(i, cor);
		carr_tmp->cur = (i - 1) * (MEM_SIZE / cor->n);
		add_curr(&carr, carr_tmp);
		i++;
	}
	return (carr);
}

void		memset_colormap(t_cw *cor, int i)
{
	unsigned int	k;

	k = 0;
	while (k < cor->ch[i].prog_size)
	{
		cor->colormap[k + i * (MEM_SIZE / cor->n)] = i + 1;
		k++;
	}
}

void		map(t_cw *cor)
{
	int				i;
	unsigned char	*code_i;

	i = 0;
	while (i < cor->n)
	{
		code_i = cor->code + i * (MEM_SIZE / cor->n);
		ft_strncpy_all((code_i), cor->ch[i].code, cor->ch[i].prog_size);
		memset_colormap(cor, i);
	}
	cor->carr = carr_list(cor);
	i = 0;
	if (cor->n)
		ft_printf("Introducing contestants...\n");
	else
		exit_print("Usage: ./corewar [-dump N | -n --stealth | -v visualizator]"
		" [-a] <champion1.cor>");
	while (i < cor->n)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
				cor->ch[i].prog_size, cor->ch[i].prog_name,
				cor->ch[i].comment);
		i++;
	}
	
}