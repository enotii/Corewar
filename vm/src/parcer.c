/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:36:34 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/24 11:45:06 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		change_pos(t_cw *cw)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cw->n)
	{
		if (!cw->m_ch[i].code && cw->m_2[j].code)
		{
			cw->m_ch[i] = cw->m_2[j];
			cw->m_ch[i].id = i;
			j++;
		}
		else if (!cw->m_ch[i].code && !cw->m_2[j].code)
			exit_print(cw, "number champ less then flag -n\n");
		i++;
	}
}

static void		dump_arg(int *i, t_cw *cw, int ac, char **av)
{
	int		y;

	y = 0;
	if (*i == (ac - 1))
		exit_print(cw, "Can't read source file -dump\n");
	cw->nbr_cyc = 0;
	cw->nbr_cyc = ft_atoi(av[*i + 1]);
	if (cw->nbr_cyc < 0)
		exit_print(cw, "dump must be positive integer or 0\n");
	*i += 2;
}

static void		take_cw_2(int ac, char **av, t_cw *cw, int *i)
{
	static int	j;

	if (!(ft_strcmp("-dump", av[*i])))
		dump_arg(i, cw, ac, av);
	else if (ft_strcmp("-a", av[*i]) == 0)
		set_aff(cw, i);
	else if (ft_strcmp("-n", av[*i]) == 0 && (*i + 2) < ac)
	{
		make_champ_n(av, ++(*i), cw);
		*i += 2;
	}
	else if (ft_strstr(av[*i], ".cor") && j < MAX_PLAYERS)
		valid_champ((*i)++, av, &(cw->m_2[j++]), cw);
	else if (ft_strcmp("-v", av[*i]) == 0 && (*i + 1) < ac
			&& ft_isdigit(av[*i + 1][0]))
		take_flag_v(cw, ft_atoi(av[*i + 1]), i);
	else if (ft_strcmp("-viz", av[*i]) == 0 && ((*i) + 1) < ac)
	{
		cw->visual.vis = 1;
		(*i)++;
	}
	else
		exit_print(cw, "Can't read source file\n");
}

static void		take_cw(int ac, char **av, t_cw *cw)
{
	int i;

	i = 1;
	while (i < ac)
		take_cw_2(ac, av, cw, &i);
}

void			*parser(int ac, char **av, t_cw *cw)
{
	int		i;
	char	*name;

	cw->nbr_cyc = -1;
	i = 0;
	while (++i < ac)
		if ((name = ft_strstr(av[i], ".cor")) && name[4] == '\0'
				&& ft_strlen(av[i]) != 4)
			cw->n++;
	if (cw->n > MAX_PLAYERS)
		exit_print(cw, "number players more than MAX_PLAYERS\n");
	take_cw(ac, av, cw);
	change_pos(cw);
	return (cw);
}
