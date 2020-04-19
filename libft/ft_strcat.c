/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 23:12:00 by caking            #+#    #+#             */
/*   Updated: 2018/12/11 02:11:33 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *restrict s1, const char *restrict s2)
{
	char	*buff;

	buff = s1;
	while (*buff != '\0')
		buff++;
	while (*s2 != '\0')
		*buff++ = *s2++;
	*buff = '\0';
	return (s1);
}
