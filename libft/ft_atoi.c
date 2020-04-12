/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhea-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 22:09:01 by caking            #+#    #+#             */
/*   Updated: 2018/12/22 08:04:54 by mrhea-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#define MAX_B	9223372036854775807

int	ft_atoi(const char *str)
{
	int					i;
	int					flag;
	unsigned long long	nb;

	i = 0;
	flag = 0;
	nb = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		flag = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		nb = (nb * 10) + ((int)str[i++] - 48);
	}
	if (nb > MAX_B && flag != 1)
		return (-1);
	if (nb > MAX_B && flag == 1)
		return (0);
	if (flag)
		return (-nb);
	return (nb);
}
