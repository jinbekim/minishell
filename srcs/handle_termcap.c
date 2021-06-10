/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_termcap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:28 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:29:36 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	get_cursor_psn(int *row, int *col)
{
	char	cursor_psn[255];
	int		read_byte;
	int		i;

	i = 0;
	write(0, "\033[6n", 4);
	read_byte = read(1, cursor_psn, 254);
	cursor_psn[read_byte] = '\0';
	while (ft_isdigit(cursor_psn[i]) == 0)
		i++;
	*row = ft_atoi(&cursor_psn[i]) - 1;
	while (cursor_psn[i] != ';')
		i++;
	*col = ft_atoi(&cursor_psn[++i]) - 1;
}

static int	put_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

static void	erase_one_char(char **backup)
{
	int		i;

	i = 0;
	while ((*backup)[i])
		i++;
	if (i != 0)
		(*backup)[i - 1] = '\0';
}

void		erase_one(char **backup)
{
	int		row;
	int		col;
	char	*cm;
	char	*ce;

	get_cursor_psn(&row, &col);
	if (backup == NULL || *backup == NULL || col < 7)
		return ;
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
	tputs(tgoto(cm, col - 1, row), 1, put_tc);
	tputs(ce, 1, put_tc);
	erase_one_char(backup);
}

void		erase_all(char *backup)
{
	int		row;
	int		col;
	char	*cm;
	char	*ce;

	if (backup == NULL || *backup == '\0')
		return ;
	get_cursor_psn(&row, &col);
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
	tputs(tgoto(cm, 6, row), 1, put_tc);
	tputs(ce, 1, put_tc);
}
