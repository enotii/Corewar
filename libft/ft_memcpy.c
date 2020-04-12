/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 22:04:14 by caking            #+#    #+#             */
/*   Updated: 2018/12/08 00:21:27 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	const char	*serc;
	char		*dest;
	size_t		i;

	i = 0;
	dest = dst;
	serc = src;
	while (i < n)
	{
		dest[i] = serc[i];
		i++;
	}
	return (dst);
}
