/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 22:17:46 by caking            #+#    #+#             */
/*   Updated: 2018/12/10 21:55:15 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*serc;
	size_t			i;

	dest = (unsigned char *)dst;
	serc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest[i] = serc[i];
		if (((char)serc[i]) == ((char)c))
		{
			return ((unsigned char *)dest + i + 1);
		}
		i++;
	}
	return (NULL);
}
