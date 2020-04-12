/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:42:45 by caking            #+#    #+#             */
/*   Updated: 2020/04/12 20:10:11 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	parse_string(char *str) //string to prebyte-code
{
	int i = 0;
	while(str[i] && (str[i] = ',' || str[i] != '"' \
	|| str[i] != '#' || str[i] != ':' || str[i] != ';' || str[i] != '%' \
	|| str[i] != ' ' || str[i] != ',' || str[i] != '\n'))
	{
		i++;
	}
}

// char	parse_file(char *filename) //file to string
// {
	
// }

int		main(int argc, char **argv)
{
	//parse_file(argv[argc - 1]);
	return(0);
}