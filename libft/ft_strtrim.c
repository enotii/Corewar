/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 00:44:22 by caking            #+#    #+#             */
/*   Updated: 2020/05/05 18:40:53 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char const *s_end;

	if (s == NULL)
		return (NULL);
	while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\v'
	|| *s == '\f' || *s == '\r')
		s++;
	if (*s == '\0')
		return (ft_strnew(0));
	s_end = s + ft_strlen(s) - 1;
	while (*s_end == ' ' || *s_end == '\t' || *s_end == '\n'
	|| *s_end == '\v' || *s_end == '\f' || *s_end == '\r')
		s_end--;
	return (ft_strsub(s, 0, s_end - s + 1));
}
