/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 23:55:19 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/18 23:55:45 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** возможно три случая
** 1 - получить номер регистра (1 байт) unsigned char
** 2 - получтить ссылку (2 байт) short
** 3 - получить 4 байта unsigned int
*/

unsigned char	read_byte_1(unsigned char *src, int i)
{
	unsigned char	c_1;

	while (i < 0)
		i += MEM_SIZE;
	c_1 = src[i % MEM_SIZE];
	return (c_1);
}

short			read_byte_2(unsigned char *src, int i)
{
	short	c_2;

	while (i < 0)
		i = MEM_SIZE + i;
	c_2 = 0;
	c_2 = (c_2 << 8);
	c_2 = c_2 | (unsigned char)src[(i) % MEM_SIZE];
	c_2 = (c_2 << 8);
	c_2 = c_2 | (unsigned char)src[(i + 1) % MEM_SIZE];
	return ((short)c_2);
}

unsigned int	read_byte_2_int(unsigned char *src, int i)
{
	unsigned int	c_2;

	while (i < 0)
		i = MEM_SIZE + i;
	c_2 = 0;
	c_2 = (c_2 << 8);
	c_2 = c_2 | (unsigned char)src[(i) % MEM_SIZE];
	c_2 = (c_2 << 8);
	c_2 = c_2 | (unsigned char)src[(i + 1) % MEM_SIZE];
	return (c_2);
}

unsigned int	read_byte_4(unsigned char *src, int i)
{
	unsigned int	c_4;

	while (i < 0)
		i = MEM_SIZE + i;
	c_4 = 0;
	c_4 = (c_4 << 8);
	c_4 = c_4 | (unsigned char)(src[(i) % MEM_SIZE]);
	c_4 = (c_4 << 8);
	c_4 = c_4 | (unsigned char)(src[(i + 1) % MEM_SIZE]);
	c_4 = (c_4 << 8);
	c_4 = c_4 | (unsigned char)(src[(i + 2) % MEM_SIZE]);
	c_4 = (c_4 << 8);
	c_4 = c_4 | (unsigned char)(src[(i + 3) % MEM_SIZE]);
	return ((unsigned int)c_4);
}

unsigned int	read_byte_4_c(unsigned char *src, int i)
{
	unsigned int	c_4;

	while (i < 0)
		i = MEM_SIZE + i;
	c_4 = 0;
	c_4 = (c_4 << 8);
	c_4 = c_4 | (char)(src[(i) % MEM_SIZE]);
	c_4 = (c_4 << 8);
	c_4 = c_4 | (char)(src[(i + 1) % MEM_SIZE]);
	c_4 = (c_4 << 8);
	c_4 = c_4 | (char)(src[(i + 2) % MEM_SIZE]);
	c_4 = (c_4 << 8);
	c_4 = c_4 | (char)(src[(i + 3) % MEM_SIZE]);
	return ((unsigned int)c_4);
}