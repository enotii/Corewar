/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:56:15 by caking            #+#    #+#             */
/*   Updated: 2020/04/12 17:12:45 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

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


char *parse_string(char *str);
#endif