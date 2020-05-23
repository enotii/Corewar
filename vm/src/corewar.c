/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Student <Student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/05/04 16:55:24 by Student          ###   ########.fr       */
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

// void	print_memory(const void *addr, size_t size)
// {
// 	size_t			i;
// 	size_t 			j;
// 	unsigned char	*p;
// 	char 			*str;

// 	str = "0123456789abcdef";
// 	p = (unsigned char *)addr;
// 	i = 0;
// 	while (i < size)
// 	{
// 		j = 0;
// 		while (j < 16 && i + j < size)
// 		{
// 			write(1, &str[(*(p + i + j)/16) % 16], 1);
// 			write(1, &str[*(p + i + j) % 16], 1);
// 				write(1, " ", 1);
// 			j += 1;
// 		}
// 		while (j < 16)
// 		{
// 			write(1, "  ", 2);
// 			if (j % 2)
// 				write(1, " ", 1);
// 			j++;
// 		}
// 		write(1, "\n", 1);
// 		i += 16;
// 	}
// }

int     main(int ac, char **av)
{
	if (ac >= 2)
	{
		int fd;
		// char *line = NULL;
		unsigned char p[4];
		fd = open(av[1], O_RDONLY);
		read(fd, p, 4);
		int i = 0;
		while (i++ < 3)
			ft_printf("%x\n", p[i]);
		if ((int)p & COREWAR_EXEC_MAGIC)
			ft_printf("zbs\n");

	}
	else
	{
		print_usage();		
		return (0);
	}
	return (0);
}