/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 00:14:53 by caking            #+#    #+#             */
/*   Updated: 2018/12/11 00:47:55 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	size_t	i;
	char	*buff;

	i = 0;
	buff = s1;
	while (*buff != '\0')
		buff++;
	while (i < n && *s2 != '\0')
	{
		*buff++ = *s2++;
		i++;
	}
	*buff = '\0';
	return (s1);
}
