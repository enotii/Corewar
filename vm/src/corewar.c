/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/14 18:35:11 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_usage(void)
{
	ft_printf("\033[0;32musage:\nflags: etc\n\033[0m");
}

int		check_name(char *name)
{
	int i;

	i = ft_strlen(name) - 1;
	if (name[i] == 'r' && name[i - 1] == 'o' && name[i - 2] == 'c' && name[i - 3] == '.')
		return (0);
	else
		return (1);
}

t_cw	*arg_analize(char **av)
{
	t_cw	*cw;
	int		i;
	int		order;

	i = 0;
	order = 0;
	if (!(cw = (t_cw *)malloc(sizeof(t_cw))))
		return (NULL);
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			if (ft_strcmp(av[i], "-n") == 0 && av[i + 1])
			{
				if (ft_atoi(av[i + 1]) >= 1 && ft_atoi(av[i + 1]) <= MAX_PLAYERS && av[i + 2])
				{
					if (check_name(av[i + 2]) == 0)
					{
						write(1, "worked\n", 6);
						
					}
				}
			}
		}
		else
		{
			if (check_name(av[i]) == 0)
			{
				write(1, "worked\n", 7);

			}
		} 
		i++;
	}
	return (cw);
}

int     main(int ac, char **av)
{
	t_cw	*cw;

	if (ac == 1)
	{
		print_usage();
		return (0);
	}
	else
	{
		cw = arg_analize(av);
	}
	return (0);
}