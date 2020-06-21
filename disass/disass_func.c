/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disass_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:44:53 by caking            #+#    #+#             */
/*   Updated: 2020/06/21 17:33:31 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int16_t			transform_int_16(int16_t integer, int is_big)
{
	int16_t	new_integer;

	if (!is_big)
	{
		new_integer = 0;
		new_integer |= (0x00FF & integer) << 8;
		new_integer |= (0xFF00 & integer) >> 8;
		integer = new_integer;
	}
	return (integer);
}

int32_t			transform_int_32(int32_t integer, int is_big)
{
	int32_t	new_integer;

	if (!is_big)
	{
		new_integer = 0;
		new_integer |= (0x000000FF & integer) << 24;
		new_integer |= (0x0000FF00 & integer) << 8;
		new_integer |= (0x00FF0000 & integer) >> 8;
		new_integer |= (0xFF000000 & integer) >> 24;
		integer = new_integer;
	}
	return (integer);
}

int				check_endianess(void)
{
	uint16_t	x;

	x = 1;
	return (*(uint8_t*)&x == 0 ? 1 : 0);
}

char			*parse_bytecode(char *filename, int *size)
{
	int		fd;
	char	*content;
	char	buffer[1000];
	int		num;
	char	*new_str;

	fd = open(filename, O_RDONLY);
	content = NULL;
	num = 0;
	new_str = NULL;
	if (fd <= 0)
	{
		ft_putstr("File does not exist");
		exit(0);
	}
	while ((num = read(fd, buffer, 1000)) > 0)
	{
		new_str = (char*)malloc(*size + num + 1);
		ft_memcpy(new_str, content, *size);
		ft_memcpy(new_str + *size, buffer, num);
		new_str[*size + num] = '\0';
		free(content);
		content = new_str;
		*size += num;
	}
	return (new_str);
}

int				get_identifier(int op_code)
{
	if (op_code == 3)
		return (INDIRECT);
	else if (op_code == 2)
		return (DIRECT);
	else
		return (REGISTER);
}
