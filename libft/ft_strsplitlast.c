/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitlast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 00:43:05 by caking            #+#    #+#             */
/*   Updated: 2020/05/05 18:57:50 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_word_len(char const *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

void			free_norm(int i, char **str2, const char *s, char c)
{
	i = -1;
	while (++i + 1 < ft_countwords(s, c))
		free(str2[i]);
	free(str2);
}

char			*ft_strsplitlast(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**str2;
	char	*ret;

	if (!s || !(str2 = (char **)malloc(sizeof(*str2) *
		(ft_countwords(s, c) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_countwords(s, c))
	{
		k = 0;
		if (!(str2[i] = ft_strnew(get_word_len(&s[j], c) + 1)))
			str2[i] = NULL;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			str2[i][k++] = s[j++];
		str2[i][k] = '\0';
	}
	ret = str2[i - 1];
	free_norm(i, str2, s, c);
	return (ret);
}
