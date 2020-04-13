/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:56:15 by caking            #+#    #+#             */
/*   Updated: 2020/04/13 17:16:15 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef enum		s_token_type
{
	STRING,
	NUMBER,
	LABEL,
	ADDRESS,
	CHAMP_NAME,
	CHAMP_COMMENT,
	LIVE,
	COMMENT,
	SEPARATOR,
	REGISTER
}					t_token_type;

typedef struct		s_token
{
	t_token_type	type;
	int				number;
	char*			string;
	char*			label;
	int				register_num;
	int				address;
	int				str_num; //for debug messages
}					t_token;

typedef struct		s_token_list
{
	t_token				token;
	struct s_token_list	*next;
}						t_token_list;

void parse_string(char *str);
#endif
