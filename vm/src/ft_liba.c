/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liba.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 14:01:00 by rdonnor           #+#    #+#             */
/*   Updated: 2020/06/24 11:38:18 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				free_cw(t_cw *cw)
{
	int		i;
	t_carriage	*carr;

	i = 0;
	carr = cw->carr;
	while (carr)
		carr = remove_head(cw, carr);
	while (i < cw->n && cw->m_ch[i].code)
	{
		free(cw->m_ch[i].code);
		free(cw->m_ch[i].file_name);
		i++;
	}
}

unsigned char		*ft_strncpy_all(unsigned char *dest,
	const unsigned char *source,
	size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

short				idx_mod(short t_ind)
{
	if (t_ind < 0)
	{
		t_ind = t_ind * (-1);
		t_ind = t_ind % IDX_MOD;
		return (-1 * t_ind);
	}
	t_ind = t_ind % IDX_MOD;
	return (t_ind);
}

int					mem_size(int cur)
{
	if (cur < 0)
	{
		while (cur < 0)
			cur += MEM_SIZE;
	}
	cur = cur % MEM_SIZE;
	return (cur);
}
