/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:05:13 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/24 11:50:16 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** запись бинарника и его валидация
** тут создается чемпион
** и место под его код
** 4 б -COREWAR_EXEC_MAGIC
** PROG_NAME_LENGTH -
** 4 б - NULL;
** 4 б prog size
*/

unsigned char	*ft_strnew_uc(size_t size)
{
	unsigned char	*ptr;

	ptr = NULL;
	ptr = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
	if (ptr)
		return ((unsigned char*)ft_memset(ptr, '\0', size + 1));
	else
		return (NULL);
}

static void		write_name_two(int fd, char *file_name, t_player *champ,
						t_cw *cw)
{
	size_t			len_code;
	unsigned char	c;

	if (champ->prog_size == 0)
		exit_print(cw, "no code\n");
	len_code = read(fd, (champ->code), champ->prog_size);
	if (len_code != champ->prog_size)
		exit_print(cw, "Error: File has a code size that differ "
			"from what its header says\n");
	while (read(fd, &c, 1))
		++len_code;
	champ->file_name = ft_strdup(file_name);
	if (len_code > CHAMP_MAX_SIZE)
	{
		ft_printf("Error: File %s has too large a code (%d bytes > %d bytes)",
			champ->file_name, len_code - 4, CHAMP_MAX_SIZE);
		exit_print(cw, "\n");
	}
	if (len_code > champ->prog_size)
		exit_print(cw, "Error: File has a code size that differ from what its "
	"header says\n");
}

void			write_name(int fd, char *file_name, t_player *champ, t_cw *cw)
{
	unsigned char	c[4];
	size_t			st;

	c[0] = 0;
	c[1] = 0;
	c[2] = 0;
	c[3] = 0;
	read(fd, &c, 4);
	champ->magic = to_int(c);
	if (champ->magic != COREWAR_EXEC_MAGIC)
		exit_print(cw, "Error: wrong exec_magic\n");
	read(fd, (champ->prog_name), PROG_NAME_LENGTH);
	if (read(fd, &c, 4) != 4 || c[0] || c[1] || c[2] || c[3])
		exit_print(cw, "Error: wrong name\n");
	if (read(fd, &c, 4) != 4)
		exit_print(cw, "File has a code size that differ "
	"from what its header says\n");
	champ->prog_size = to_int(c);
	if ((st = read(fd, &(champ->comment), COMMENT_LENGTH)) != COMMENT_LENGTH)
		exit_print(cw, "error comment\n");
	if ((st = read(fd, &c, 4)) != 4 || c[0] || c[1] || c[2] || c[3])
		exit_print(cw, "no NULL in comment\n");
	champ->code = (unsigned char *)ft_strnew_uc(champ->prog_size);
	write_name_two(fd, file_name, champ, cw);
}

void			valid_champ(int i, char **av, t_player *champ, t_cw *cw)
{
	char	*name;
	int		fd;

	if ((name = ft_strstr(av[i], ".cor")) && name[4] == '\0'
			&& ft_strlen(av[i]) != 4)
	{
		if ((fd = open(av[i], O_RDONLY)) > 2)
		{
			write_name(fd, av[i], champ, cw);
		}
		if (champ->file_name)
			return ;
		else
			exit_print(cw, "not valid champ file\n");
	}
	else
		exit_print(cw, "not valid champ name\n");
}

/*
** i - номер текущего параметра
** если параметр файл cw пытаемся записать чемпиона
*/

/*
** сохраняет чемпиона с флагом -n в m_ch[i - 1], если там не занято
** если занято в cw->m_2[i] (пока i занято шагаем дальше)
** -n number
** sets the number of the next player. If non-existent,
** the player will have the next
** available number in the order of the parameters. The last player
** will have the first
** process in the order of execution
** если флаг n - сразу запишем валиднгого игрока
** n - текущий параметр
** i - номер чеммпиона, после флага n (Оно должно быть больше или равно 1,
** но не превышать общее количество игроков, которые принимают участие в битве).
*/

void			make_champ_n(char **av, int n, t_cw *cw)
{
	int	i;

	i = ft_atoi(av[n]);
	if (i < 1)
		exit_print(cw, "n must be positive integer\n");
	else if (i && i <= cw->n)
	{
		if (!(cw->m_ch[i - 1]).code)
		{
			valid_champ(++n, av, &(cw->m_ch[i - 1]), cw);
			cw->m_ch[i - 1].id = i - 1;
		}
		else
			exit_print(cw, "not available n\n");
	}
}
