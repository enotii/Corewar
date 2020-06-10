/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/11 01:01:28 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_usage(void)
{
	ft_printf("\033[0;32musage:\nflags: etc\n\033[0m");
}

/*
** void	print_memory(const void *addr, size_t size)
** {
** 	size_t			i;
** 	size_t 			j;
** 	unsigned char	*p;
** 	char 			*str;
** 	
**	str = "0123456789abcdef";
** 	p = (unsigned char *)addr;
** 	i = 0;
** 	while (i < size)
** 	{
** 		j = 0;
** 		while (j < 16 && i + j < size)
** 		{
** 			write(1, &str[(*(p + i + j)/16) % 16], 1);
** 			write(1, &str[*(p + i + j) % 16], 1);
** 				write(1, " ", 1);
** 			j += 1;
** 		}
** 		while (j < 16)
** 		{
** 			write(1, "  ", 2);
** 			if (j % 2)
** 				write(1, " ", 1);
** 			j++;
** 		}
** 		write(1, "\n", 1);
** 		i += 16;
** 	}
** }
/*

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

static void		dump_arg(int i, t_cw *cor, int ac, char **av)
{
	if (i == (ac - 1))
		exit_print("Can't read source file -dump");
	cor->nbr_cyc = 0;
	cor->nbr_cyc = ft_atoi(av[i + 1]);
}

static void	init_players(int ac, char	**av, t_cw *cor)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		if (!(ft_strcmp("-dump", av[i])))
		{
			dump_arg(i, cor, ac, av);
			i += 2;
		}
		else if (ft_strcmp("-n", av[i]) == 0 && (i + 2) < ac)
		{
			make_champ_n(av, ++i, cor);
			i += 2;
		}
		else if (ft_strstr(av[i], ".cor") && j < MAX_PLAYERS)
			valid_champ((i)++, av, &(cor->ch_tmp[j++]));
		else
			exit_print("Can't read source file\n");
	}
}

void	parser(int ac, char **av, t_cw *cor)
{
	int 	i;
	char	*name;

	cor->nbr_cyc = -1;
	i = 0;
	while (++i < ac)
		if ((name = ft_strstr(av[i], ".cor")) && name[4] == "\0" 
			&& ft_strlen(av[i]) != 4)
		cor->n++;
	if (cor->n > MAX_PLAYERS)
		exit_print("Number of players more than MAX_PLAYERS\n");
	init_players(ac, av, cor);
	
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
	}
	else
	{
		print_usage();
	}
	return (0);
}