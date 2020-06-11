/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:05:13 by sscottie          #+#    #+#             */
/*   Updated: 2020/06/11 15:26:27 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** запись бинарника и его валидация
** тут создается чемпион
** и место под его код
** 4 б - COREWAR_EXEC_MAGIC
** PROG_NAME_LENGTH -
** 4 б - NULL;
** 4 б prog size
*/

static void		write_code(int fd, char *file_name, t_player *player)
{
	size_t			len_code;
	unsigned char	c;

	len_code = read(fd, (player->code), player->prog_size);
	if (len_code != player->prog_size)
		exit_print("Error: File has a code size that differ "
			"from what its header says\n");
	while (read(fd, &c, 1))
		++len_code;
	player->file_name = ft_strdup(file_name);
	if (len_code > CHAMP_MAX_SIZE)
	{
		ft_printf("Error: File %s has too large a code (%d bytes > %d bytes)\n",
			player->file_name, len_code - 4, CHAMP_MAX_SIZE);
		exit_print("Error: File has too large");
	}
	if (len_code > player->prog_size)
		exit_print("Error: File has a code size that differ from what its "
	"header says\n");
}

void			write_header(int fd, char *file_name, t_player *player)
{
	unsigned char	c[4];
	size_t			st;

	read(fd, &c, 4);
	player->magic = ft_uc_to_int(c);
	if (player->magic != COREWAR_EXEC_MAGIC)
		exit_print("Error: wrong exec_magic\n");
	read(fd, (player->prog_name), PROG_NAME_LENGTH);
	if (read(fd, &c, 4) != 4 || c[0] || c[1] || c[2] || c[3])
		exit_print("Error: wrong name/must be NULL between name and size\n");
	if (read(fd, &c, 4) != 4 ||
		(player->prog_size = ft_uc_to_int(c)) > CHAMP_MAX_SIZE)
		exit_print("File has a code size that differ "
	"from what its header says\n");
	if ((st = read(fd, &(player->comment), COMMENT_LENGTH)) != COMMENT_LENGTH)
		exit_print("error comment\n");
	if ((st = read(fd, &c, 4)) != 4 || c[0] || c[1] || c[2] || c[3])
		exit_print("no NULL in comment\n");
	player->code = (unsigned char *)ft_strnew_uc(player->prog_size);
	write_code(fd, file_name, player);
}


/*
** i - номер текущего параметра
** если параметр файл cor пытаемся записать чемпиона
*/

void			valid_player(int i, char **av, t_player *player)
{
	char	*name;
	int		fd;

	if ((name = ft_strstr(av[i], ".cor")) && name[4] == '\0'
			&& ft_strlen(av[i]) != 4)
	{
		if ((fd = open(av[i], O_RDONLY)) > 2)
		{
			write_header(fd, av[i], player);
		}
		if (player->file_name)
			return ;
		else
			exit_print("not valid player file\n");
	}
	else
		exit_print("not valid player name\n");
}

/*
** сохраняет чемпиона с флагом -n в m_ch[i - 1], если там не занято
** если занято в cor->m_2[i] (пока i занято шагаем дальше)
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

void			make_player_n(char **av, int n, t_cw *cor)
{
	int	i;

	i = ft_atoi(av[n]);
	if (i && i <= cor->n)
	{
		if (!(cor->ch[i - 1]).code)
		{
			valid_player(++n, av, &(cor->ch[i - 1]));
			cor->ch[i - 1].id = i - 1;
		}
		else
			exit_print("not available n\n");
	}
	else
	{
		i = 0;
		while (cor->ch_tmp[i].code)
			i++;
		valid_player(++n, av, &(cor->ch_tmp[i]));
	}
}