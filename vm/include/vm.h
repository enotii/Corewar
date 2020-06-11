/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 03:27:18 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/11 15:20:09 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "ft_printf.h"

# define RUNNING 			713
# define CYCLE_PER_SEC		1225
# define CYCLE_COORD		1993
# define PROCESSES			2505
# define PL_ONE_LIVE		3529
# define M MEM_SIZE

# define LIVE_CODE	0x01
# define LD_CODE 	0x02
# define ST_CODE	0x03
# define ADD_CODE	0x04
# define SUB_CODE	0x05
# define AND_CODE	0x06
# define OR_CODE	0x07
# define XOR_CODE	0x08
# define ZJMP_CODE	0x09
# define LDI_CODE	0x0a
# define STI_CODE	0x0b
# define FORK_CODE	0x0c
# define LLD_CODE	0x0d
# define LLDI_CODE	0x0e
# define LFORK_CODE	0x0f
# define AFF_CODE	0x10

# define LIVE_CYCLE_CD	10
# define LD_CYCLE_CD	5
# define ST_CYCLE_CD	5
# define ADD_CYCLE_CD	10
# define SUB_CYCLE_CD	10
# define AND_CYCLE_CD	6
# define OR_CYCLE_CD	6
# define XOR_CYCLE_CD	6
# define ZJMP_CYCLE_CD	20
# define LDI_CYCLE_CD	25
# define STI_CYCLE_CD	25
# define FORK_CYCLE_CD	800
# define LLD_CYCLE_CD	10
# define LLDI_CYCLE_CD	50
# define LFORK_CYCLE_CD	1000
# define AFF_CYCLE_CD	2

/*
**static t_op			g_op_tab[16] = {
**	{
**			.name = "live",
**			.code = 0x01,
**			.args_num = 1,
**			.args_types_code = 0,
**			.args_types = {T_DIR, 0, 0},
**			.t_dir_size = 4,
**	},
**	{
**			.name = "ld",
**			.code = 0x02,
**			.args_num = 2,
**			.args_types_code = 1,
**			.args_types = {T_DIR | T_IND, T_REG, 0},
**			.t_dir_size = 4,
**	},
**	{
**			.name = "st",
**			.code = 0x03,
**			.args_num = 2,
**			.args_types_code = 1,
**			.args_types = {T_REG, T_REG | T_IND, 0},
**			.t_dir_size = 4,
**	},
**	{
**			.name = "add",
**			.code = 0x04,
**			.args_num = 3,
**			.args_types_code = 1,
**			.args_types = {T_REG, T_REG, T_REG},
**			.t_dir_size = 4,
**	},
**	{
**			.name = "sub",
**			.code = 0x05,
**			.args_num = 3,
**			.args_types_code = 1,
**			.args_types = {T_REG, T_REG, T_REG},
**			.t_dir_size = 4,
**	},
**	{
**			.code = 0x06,
**			.name = "and",
**			.args_num = 3,
**			.args_types_code = 1,
**			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
**			.t_dir_size = 4,
**	},
**	{
**			.name = "or",
**			.code = 0x07,
**			.args_num = 3,
**			.args_types_code = 1,
**			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
**			.t_dir_size = 4,
**	},
**	{
**			.name = "xor",
**			.code = 0x08,
**			.args_num = 3,
**			.args_types_code = 1,
**			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
**			.t_dir_size = 4,
**	},
**	{
**			.name = "zjmp",
**			.code = 0x09,
**			.args_num = 1,
**			.args_types_code = 0,
**			.args_types = {T_DIR, 0, 0},
**			.t_dir_size = 2,
**	},
**	{
**			.name = "ldi",
**			.code = 0x0A,
**			.args_num = 3,
**			.args_types_code = 1,
**			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
**			.t_dir_size = 2,
**	},
**	{
**			.name = "sti",
**			.code = 0x0B,
**			.args_num = 3,
**			.args_types_code = 1,
**			.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
**			.t_dir_size = 2,
**	},
**	{
**			.name = "fork",
**			.code = 0x0C,
**			.args_num = 1,
**			.args_types_code = 0,
**			.args_types = {T_DIR, 0, 0},
**			.t_dir_size = 2,
**	},
**	{
**			.name = "lld",
**			.code = 0x0D,
**			.args_num = 2,
**			.args_types_code = 1,
**			.args_types = {T_DIR | T_IND, T_REG, 0},
**			.t_dir_size = 4,
**	},
**	{
**			.name = "lldi",
**			.code = 0x0E,
**			.args_num = 3,
**			.args_types_code = 1,
**			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
**			.t_dir_size = 2,
**	},
**	{
**			.name = "lfork",
**			.code = 0x0F,
**			.args_num = 1,
**			.args_types_code = 0,
**			.args_types = {T_DIR, 0, 0},
**			.t_dir_size = 2,
**	},
**	{
**			.name = "aff",
**			.code = 0x10,
**			.args_num = 1,
**			.args_types_code = 1,
**			.args_types = {T_REG, 0, 0},
**			.t_dir_size = 4,
**	}
**};
*/



typedef	struct			s_player
{
	unsigned int		id;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	unsigned int		magic;
	unsigned char		*code;
	char				*file_name;
}						t_player;

/*
** каретка:
** Название регистра (r1, r2...) в байт-коде занимает 1 байт.
** Но сам регистр вмещает в себя 4 байта, как указано в константе REG_SIZE.
** num - уникальный номер каретки !!! ЗАЧЕМ?
** cur - текущее положение
** cycles_live - цикл когда проводилась оп live
** carry - Carry - нужен в функции zjmp, который исполняется в том случае, что
** у каретки->carry = 1.
** id_par - родитель
** reg
** live -  1 или 0 жива или нет
** prog - команду которую он исполняет
** cycles_to - количество циклов, сколько ему осталось ждать
** до исполнения команды.
** i - перемещение каретки на шаге (длина предыдущего хода)
*/

typedef	struct			s_carriage
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

/*
** все о текущем положении и live:
** id_live - игрок, о котором в последний раз сказали, что он жив (ПОБЕДИТЕЛЬ)
** ИНФОРМАЦИЮ О НЁМ МЫ ПОЛУЧАЕМ ТОЛЬКО В оп_LIVE ????
** cyc - количество прошедших с начала игры циклов
** live_count - количество выполненных операций live за последний период,
** длинной в cyc_to_die
** обнуляется каждую проверку?
** cyc_to_die - длительность периода до проверки
** изменяется в 2ух случаях
** check_count - количество проведенных проверок
** - обнуляется, если меняется cyc to die
** cycle_new - кол -во циклов после обнуления
** counter - считает проверки без изменения to_die
*/

typedef struct			s_live
{
	int					id_live;
	int					cyc;
	int					live_count;
	int					cyc_to_die;
	int					cyc_tmp;
	int					counter;
}						t_live;

/*
** Общая структура для игры
** n - общее кол - во игроков
** n_curr - число кареток в настоящий момент
** nbr_cyc - если есть dump
** f - набор флажков для заполнения с флагом -n
** m_ch - основной хранитель чемпионов
** (хранит ссылки на m_2)
** m_2 - туда пишем чемпионов, в очередности поступления(без флагов)
** code - все игровое поле
** carr - список всех кареток
** live
** нет общего числа кареток больше
*/

typedef	struct			s_cw
{
	int					n;
	int					n_curr;
	int					nbr_cyc;
	int					v_print[4];
	int					f[MAX_PLAYERS];
	unsigned char		code[MEM_SIZE];
	unsigned char		colormap[MEM_SIZE];
	unsigned char		bold[MEM_SIZE];
	int					addr1;
	int					addr2;
	int					aff;
	t_carriage			*carr;
	t_player			ch[MAX_PLAYERS];
	t_player			ch_tmp[MAX_PLAYERS];
	t_live				live;
}						t_cw;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header_s;

void	parser(int ac, char **av, t_cw *cor);
void	exit_print(char *str);
void	make_player_n(char **av, int n, t_cw *cor);
void	valid_player(int i, char **av, t_player *player);
void	write_header(int fd, char *file_name, t_player *player);


#endif
