#ifndef VM_H
# define VM_H

# include "op.h"
# include "ft_printf.h"

# define RUNNING 			713
# define CYCLE_PER_SEC		1225
# define CYCLE_COORD		1993
# define PROCESSES			2505
# define PL_ONE_LIVE		3529

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

// static t_op			g_op_tab[16] = {
// 	{
// 			.name = "live",
// 			.code = 0x01,
// 			.args_num = 1,
// 			.args_types_code = 0,
// 			.args_types = {T_DIR, 0, 0},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "ld",
// 			.code = 0x02,
// 			.args_num = 2,
// 			.args_types_code = 1,
// 			.args_types = {T_DIR | T_IND, T_REG, 0},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "st",
// 			.code = 0x03,
// 			.args_num = 2,
// 			.args_types_code = 1,
// 			.args_types = {T_REG, T_REG | T_IND, 0},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "add",
// 			.code = 0x04,
// 			.args_num = 3,
// 			.args_types_code = 1,
// 			.args_types = {T_REG, T_REG, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "sub",
// 			.code = 0x05,
// 			.args_num = 3,
// 			.args_types_code = 1,
// 			.args_types = {T_REG, T_REG, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.code = 0x06,
// 			.name = "and",
// 			.args_num = 3,
// 			.args_types_code = 1,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "or",
// 			.code = 0x07,
// 			.args_num = 3,
// 			.args_types_code = 1,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "xor",
// 			.code = 0x08,
// 			.args_num = 3,
// 			.args_types_code = 1,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "zjmp",
// 			.code = 0x09,
// 			.args_num = 1,
// 			.args_types_code = 0,
// 			.args_types = {T_DIR, 0, 0},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "ldi",
// 			.code = 0x0A,
// 			.args_num = 3,
// 			.args_types_code = 1,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "sti",
// 			.code = 0x0B,
// 			.args_num = 3,
// 			.args_types_code = 1,
// 			.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "fork",
// 			.code = 0x0C,
// 			.args_num = 1,
// 			.args_types_code = 0,
// 			.args_types = {T_DIR, 0, 0},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "lld",
// 			.code = 0x0D,
// 			.args_num = 2,
// 			.args_types_code = 1,
// 			.args_types = {T_DIR | T_IND, T_REG, 0},
// 			.t_dir_size = 4,
// 	},
// 	{
// 			.name = "lldi",
// 			.code = 0x0E,
// 			.args_num = 3,
// 			.args_types_code = 1,
// 			.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "lfork",
// 			.code = 0x0F,
// 			.args_num = 1,
// 			.args_types_code = 0,
// 			.args_types = {T_DIR, 0, 0},
// 			.t_dir_size = 2,
// 	},
// 	{
// 			.name = "aff",
// 			.code = 0x10,
// 			.args_num = 1,
// 			.args_types_code = 1,
// 			.args_types = {T_REG, 0, 0},
// 			.t_dir_size = 4,
// 	}
// };




typedef	struct			s_player
{
	int					num;
	char				*name;
	char				*comment;
	int					exec_size;
	char				*exec;
	struct s_player		*next;
}						t_player;

typedef	struct			s_carriage
{
	int					num_of_carriage;
	int					carry;
	int					regs[REG_NUMBER];

	struct s_carriage	*next;
	struct s_carriage	*prev;
}						t_carriage;
typedef	struct	s_cw
{
	t_carriage		*cart;
	t_player		*champs;

}				t_cw;




#endif
