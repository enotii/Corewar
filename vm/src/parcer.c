/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:36:34 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/11 15:21:36 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		swap_players(t_cw *cor)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cor->n)
	{
		if (!cor->ch[i].code && cor->ch_tmp[j].code)
		{
			cor->ch[i] = cor->ch_tmp[j];
			cor->ch[i].id = i;
			j++;
		}
		else if (!cor->ch[i].code && !cor->ch_tmp[j].code)
			exit_print("player's number less then flag -n");
		i++;
	}
}

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
			make_player_n(av, ++i, cor);
			i += 2;
		}
		else if (ft_strstr(av[i], ".cor") && j < MAX_PLAYERS)
			valid_player((i)++, av, &(cor->ch_tmp[j++]));
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
		if ((name = ft_strstr(av[i], ".cor")) && name[4] == '\0' 
			&& ft_strlen(av[i]) != 4)
		cor->n++;
	if (cor->n > MAX_PLAYERS)
		exit_print("Number of players more than MAX_PLAYERS\n");
	init_players(ac, av, cor);
	swap_players(cor);
}