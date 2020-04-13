/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:56:15 by caking            #+#    #+#             */
/*   Updated: 2020/04/13 17:08:32 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"

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
	t_token			token;
	t_token_list	*next;

}					t_token_list;


// typedef	struct		s_figure
// {
// 	char			alpha;
// 	char			**figure;
// 	struct s_figure	*next;
// 	int				width;
// 	int				length;
// 	int				coords[2];
// 	int				count;
// }					t_figure;


void parse_string(char *str);
#endif
