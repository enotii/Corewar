/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caking <caking@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 15:56:15 by caking            #+#    #+#             */
/*   Updated: 2020/05/01 18:20:39 by caking           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "../libft/libft.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

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
	REGISTER, //done
	COMMENT
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

typedef struct		s_command
{
	int				is_label;
	int				str_num;
	int				op_code;
	int				types[3];
	int				values[3];
	char			*labels[3];
}					t_command;

typedef struct		s_command_list
{
	t_command		command;
	struct s_command_list	*next;
}					t_command_list;

typedef struct		s_label_list
{
	char			*label_name;
	int				label_position;
	struct s_label_list	*next;
}					t_label_list;

typedef struct		s_program
{
	t_header		header;
	t_command_list	*list;
	t_label_list	*labels;
}					t_program;

char			*parse_file(char *filename);
t_token_list	*file_to_tokens(char *str);
t_token_list	*get_next_token(char **orig_string);
void			addlstname(t_token_list	*ret);
void			addlstcomment(t_token_list	*ret);
int				skip_whitespaces(char *str, int *countstr);
void			addseparator(t_token_list	*ret, int *i);
int				addlabel(t_token_list *ret, char *substring, int *i);
int				puterror(int i);
int				addstring(t_token_list *ret, char *str, int *countstr);
int				skip_until_next_token(int i, char *str);
int				check_commands(char *substring);
int				add_command(t_token_list *ret, int j);
int				adddirectarg(t_token_list *ret, char *str, int *i);
int				addregisterarg(t_token_list *ret, char *substring);
int				addindirectarg(t_token_list *ret, char *str);
int				addindirectlabelarg(t_token_list *ret, char *str, int *i);
char			*commands_to_bytecode(t_program program, char *filename);
char			form_byte_args(t_command *command);
int32_t			transform_int_32(int32_t integer, int is_big);
int16_t			transform_int_16(int16_t integer, int is_big);
void			handle_name(t_token_list **tokens, t_program *program);
void			handle_comment(t_token_list **tokens, t_program *program);
void			manage_args(t_token_list **list, t_command_list *result, t_program *prog);
t_command_list	*get_next_command(t_token_list **list, t_program *prog, t_label_list **last_label);
void			replace_one_label_by_value(t_command *command, int count, t_label_list *list, int bytes, int args_bytes);
void			replace_labels_with_values(t_program *prog);
t_program		tokens_to_commands(t_token_list *tokens);
#endif
