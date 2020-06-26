/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 03:27:18 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/26 15:45:08 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "ft_printf.h"
# include <ncurses.h>
# include "op.h"

# define DELAY 14000
# define M MEM_SIZE

typedef struct			s_viz
{
	int					vis;
	int					delay;
	WINDOW				*main_win;
	WINDOW				*side_win;
	int					pause;
}						t_viz;

typedef struct			s_player
{
	unsigned int		id;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	unsigned int		magic;
	unsigned char		*code;
	char				*file_name;
}						t_player;

typedef struct			s_carriage
{
	int					num;
	int					cur;
	int					cycles_live;
	int					carry;
	int					id_par;
	int					reg[REG_NUMBER];
	unsigned char		prog;
	int					cycles_to;
	int					i;
	struct s_carriage	*next;
}						t_carriage;

typedef struct			s_live
{
	int					id_live;
	int					cyc;
	int					live_count;
	int					cyc_to_die;
	int					cyc_tmp;
	int					counter;
}						t_live;

typedef struct			s_cw
{
	int					n;
	int					n_curr;
	int					nbr_cyc;
	int					v_print[4];
	int					f[MAX_PLAYERS];
	t_player			m_ch[MAX_PLAYERS];
	t_player			m_2[MAX_PLAYERS];
	unsigned char		code[MEM_SIZE];
	unsigned char		colormap[MEM_SIZE];
	unsigned char		bold[MEM_SIZE];
	t_viz				visual;
	struct s_carriage	*carr;
	struct s_live		live;
	int					addr1;
	int					addr2;
	int					aff;
}						t_cw;

/*
 ****** parser ******
*/

void					*parser(int ac, char **av, t_cw *cw);

/*
 * ***** champ ******
*/

void					write_name(int fd, char *file_name,
							t_player *champ, t_cw *cw);
void					valid_champ(int i, char **av,
							t_player *champ, t_cw *cw);
void					make_champ_n(char **av, int n, t_cw *cw);

/*
 * ****** map ******
*/

void					map(t_cw *cw);

/*
 * ***** start_game ******
*/

void					start_game(t_cw *cw);

/*
 * ***** carr_list ******
*/

t_carriage				*new_curr(int id_par, t_cw *cw);
void					add_curr(t_carriage **all_carr, t_carriage *new);
int						len_curr(t_carriage *list);
t_carriage				*remove_head(t_cw *cw, t_carriage *curr);
t_carriage				*remove_elem(t_carriage *curr,
							t_carriage **prev, t_cw *cw);
t_carriage				*carr_list(t_cw *cw);

/*
 * ***** do_op ******
*/

int						ft_cycles_to(char p);
void					do_op(t_cw *cw, t_carriage	*tmp);

/*
 * ***** print_code ******
*/

void					print_dump_code(t_cw *cw);
void					exit_print(t_cw *cw, char *str);
void					print_adv(t_cw *cw, t_carriage *tmp);
void					take_flag_v(t_cw *cw, int num, int *i);
/*
** ***** read_byte ******
** inttobyte - переводит инт в байт
** base16_2_cw - из одного байта делает 8 бит
*/

unsigned char			read_byte_1 (unsigned char *src, int i);
short					read_byte_2 (unsigned char *src, int i);
unsigned int			read_byte_2_int (unsigned char *src, int i);
unsigned int			read_byte_4 (unsigned char *src, int i);
unsigned int			read_byte_4_c (unsigned char *src, int i);
unsigned char			*inttobyte(int a, t_cw *cw);
char					*base16_2_cw(t_cw *cw, t_carriage *tmp);

/*
** ***** ft_liba ******
*/

void					free_cw(t_cw *cw);
unsigned char			*ft_strncpy_all(unsigned char *dest,
			const unsigned char *source, size_t n);
int						mem_size(int cur);
short					idx_mod(short t_ind);
unsigned char			*ft_strnew_uc(size_t size);
int						val_reg(unsigned char reg);
int						to_int(unsigned char *c);
int						mem(int x);
/*
** ***** ft_add ******
** arg_4 - считает откуда считывать 4 байта, если возможные аргументы t_reg,
** t_dir(4 байта) или t_ind
** arg_2 - считает откуда считывать 4 байта  t_dir(2 байта) или t_ind
*/

void					ft_add(t_cw *cw, t_carriage *tmp);
void					ft_zjmp(t_cw *cw, t_carriage *tmp);
int						arg_4(char *b2, t_carriage *tmp, t_cw *cw, int *f_err);
int						arg_2(char *b2, t_carriage *tmp, t_cw *cw, int *f_err);

/*
** все операции, что с флагом l - реализованы с переменной l
** про операции в файлах с функциями
*/

void					ft_live(t_cw *cw, t_carriage *tmp);
void					ft_ld(t_cw *cw, t_carriage *tmp, int l);
void					ft_st(t_cw *cw, t_carriage *tmp);
void					ft_sub(t_cw *cw, t_carriage *tmp);
void					ft_and(t_cw *cw, t_carriage *tmp);
void					ft_or(t_cw *cw, t_carriage *tmp);
void					ft_xor(t_cw *cw, t_carriage *tmp);
void					ft_ldi(t_cw *cw, t_carriage *tmp);
void					ft_sti(t_cw *cw, t_carriage *tmp);
t_carriage				*ft_fork(t_cw *cw, t_carriage *tmp, int l);
void					ft_lld(t_cw *cw, t_carriage *tmp);
void					ft_aff(t_cw *cw, t_carriage *tmp);
void					copy_p(void *dst, const void *src, int d_s, int s_s);
void					set_aff(t_cw *cw, int *i);

/*
** viz
*/

void					init_window(t_cw *cw);
void					create_field(t_cw *cw);
void					render(t_cw *cw);
WINDOW					*create_newwin(int height, int width, int sty, int stx);
void					side_panel(WINDOW *side_win, t_cw *cw);
int						players(WINDOW *side_win, int line, t_cw *cw);
void					main_panel(WINDOW *main_win, t_cw *tool);
void					paint_carg(t_cw *cw);
void					visual(t_cw *cw);
int						graph_cycle(t_cw *cw);
void					write_map_color(t_cw *cw, int pos,
							int len, t_carriage *carg);
void					end_game(t_cw *cw);
void					stop_visual(t_cw *cw);
void					panel_help(t_cw *cw, WINDOW *main_win, int i, int line);

#endif
