/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_parent_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 23:55:13 by caking            #+#    #+#             */
/*   Updated: 2018/12/19 00:18:05 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_parent_path(char *path)
{
	char	*last_slash;
	char	*parent;

	last_slash = strrchr(path, '/');
	parent = strndup(path, last_slash - path);
	return (parent);
}
