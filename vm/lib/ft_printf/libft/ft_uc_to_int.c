/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uc_to_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 15:22:48 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/11 15:24:32 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_uc_to_int(unsigned char *c)
{
    return((c[0] << 24) | (c[1] << 16) | (c[2] << 8) | c[3]);
}