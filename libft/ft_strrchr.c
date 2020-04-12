/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:38:32 by caking            #+#    #+#             */
/*   Updated: 2018/12/16 21:38:46 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *str;

	str = s;
	while (*str)
		str++;
	if (c == 0)
		return ((char*)str);
	while (str > s)
	{
		str--;
		if (((unsigned char)*str) == c)
			return ((char*)str);
	}
	return (0);
}
