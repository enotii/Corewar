/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/19 00:42:28 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_usage(void)
{
	ft_printf("\033[0;32musage:\nflags: etc\n\033[0m");
}

int			to_int(unsigned char *c)
{
	return ((c[0] << 24) | (c[1] << 16) | (c[2] << 8) | c[3]);
}

int			val_reg(unsigned char reg)
{
	return ((reg > 0 && reg <= REG_NUMBER) ? 1 : 0);
}

/*
**		else if (ft_strcmp("-v", av[i]) == 0 && (i + 1) < ac
**				&& ft_isdigit(av[i + 1][0]))
**			take_flag_v(cor, ft_atoi(av[i + 1]), i);
**		else if (ft_strcmp("-viz", av[i]) == 0 && ((i) + 1) < ac)
**		{
**			cor->visual.vis = 1;
**			(*i)++;
**		}
**		else if (ft_strcmp("-a", av[i]) == 0)
**			set_aff(cor, i);
*/

void				free_cor(t_cw *cor)
{
	int			i;
	t_carriage	*carr;

	i = 0;
	carr = cor->carr;
	while (carr)
		carr = remove_head(cor, carr);
	while (i < cor->n && cor->ch[i].code)
	{
		free(cor->ch[i].code);
		free(cor->ch[i].file_name);
		i++;
	}
}

static void	zero_live(t_cw *cor)
{
	cor->live.cyc_tmp = 0;
	cor->live.id_live = cor->n;
	cor->live.cyc = 0;
	cor->live.live_count = 0;
	cor->live.cyc_to_die = CYCLE_TO_DIE;
	cor->aff = 0;
}

static void	init_flags(t_cw *cor)
{
	cor->v_print[0] = -1;
	cor->v_print[1] = -1;
	cor->v_print[2] = -1;
	cor->v_print[3] = -1;
}

void	exit_print(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

/*
** parse_av - просматривает аргументы,
** инициальзирует главную структуру
** arena - если чемпионы валидны
** 	cor->code = (char *)ft_memalloc(sizeof(char) * MEM_SIZE);
**	cor->live = (t_live *)ft_memalloc(sizeof(t_live));
**	cor->colormap = (int *)ft_memalloc(sizeof(int) * MEM_SIZE);
** go_cor - cама игра
*/

int     main(int ac, char **av)
{
	static t_cw	cor;

	if (ac >= 2)
	{
		init_flags(&cor);
		parser(ac, av, &cor);
		map(&cor);
		zero_live(&cor);
		go_cor(&cor);
		if (cor.n)
			ft_printf("Contestant %d, \"%s\", has won !\n", cor.live.id_live,
				(cor.ch[cor.live.id_live - 1]).prog_name);
		free_cor(&cor);
	}
	else
	{
		print_usage();
	}
	return (0);
}