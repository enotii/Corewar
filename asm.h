/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:56:15 by caking            #+#    #+#             */
/*   Updated: 2020/04/21 18:45:42 by caking           ###   ########.fr       */
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
# include <stdio.h>

# define LABEL_ERROR 1
# define REGISTER_ERROR 2
# define LEXIC_ERROR 3

typedef enum		s_token_type
{
	STRING, //done
	DIRECT, //done
	DIRECT_LABEL,
	LABEL, //done
	INDIRECT, //done
	INDIRECT_LABEL, //done
	CHAMP_NAME, //done
	CHAMP_COMMENT, //done
	OPERATION, //done
	SEPARATOR, //done
	REGISTER //done
}					t_token_type;

typedef struct		s_token
{
	t_token_type	type;
	int				direct;
	int				indirect;
	char*			string;
	char*			label;
	int				register_num;
	char			*indirect_label;
	char			*direct_label;
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
void			addseparator(t_token_list	*ret, int *i);
int				addlabel(t_token_list *ret, char *substring, int *i);
int				puterror(int i);
int				addstring(t_token_list *ret, char *str);
int				skip_until_next_token(int i, char *str);
int				check_commands(char *substring);
int				add_command(t_token_list *ret, int j);
int				adddirectarg(t_token_list *ret, char *str, int *i);
int				addregisterarg(t_token_list *ret, char *substring);
int				addindirectarg(t_token_list *ret, char *str);
int				addindirectlabelarg(t_token_list *ret, char *str, int *i);
#endif
