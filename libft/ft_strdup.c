/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 21:58:10 by caking            #+#    #+#             */
/*   Updated: 2018/12/10 22:47:42 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		lenght;
	int		i;

	i = 0;
	lenght = ft_strlen(s1);
	s2 = (char*)malloc(sizeof(*s2) * (lenght + 1));
	if (s2 == NULL)
		return (0);
	while (i < lenght)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
