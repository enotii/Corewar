/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/11 15:20:31 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_usage(void)
{
	ft_printf("\033[0;32musage:\nflags: etc\n\033[0m");
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
		// arena(&cor);
		// zero_live(&cor);
		// go_cor(&cor);
		// if (cor.n)
		// 	ft_printf("Contestant %d, \"%s\", has won !\n", cor.live.id_live,
		// 		(cor.ch[cor.live.id_live - 1]).prog_name);
		// free_cor(&cor);
	}
	else
	{
		print_usage();
	}
	return (0);
}