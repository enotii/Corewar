/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:56:15 by caking            #+#    #+#             */
/*   Updated: 2020/04/16 22:12:26 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft/libft.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

typedef enum		s_token_type
{
	STRING,
	NUMBER,
	LABEL,
	ADDRESS,
	CHAMP_NAME, //done
	CHAMP_COMMENT, //done
	OPERATION,
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
	int				op_code;
	int				str_num; //for debug messages
}					t_token;

typedef struct		s_token_list
{
	t_token				token;
	struct s_token_list	*next;
}						t_token_list;

char			*parse_file(char *filename);
t_token_list	*file_to_tokens(char *str);
t_token_list	*get_next_token(char **orig_string);
void			addlstname(t_token_list	*ret);
void			addlstcomment(t_token_list	*ret);
int				skip_whitespaces(char *str);
#endif
