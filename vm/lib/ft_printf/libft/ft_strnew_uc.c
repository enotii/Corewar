/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_uc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 14:38:20 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/11 14:39:16 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	*ft_strnew_uc(size_t size)
{
	unsigned char	*ptr;

	ptr = NULL;
	ptr = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
	if (ptr)
		return ((unsigned char*)ft_memset(ptr, '\0', size + 1));
	else
		return (NULL);
}