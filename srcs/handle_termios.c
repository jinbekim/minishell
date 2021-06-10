/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_termios.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:30 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:29:20 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static struct termios		*get_input_termios(void)
{
	static struct termios	input_set;
	static int				first_once = 1;

	if (first_once == 1)
	{
		tcgetattr(STDIN_FILENO, &input_set);
		input_set.c_lflag &= ~(ICANON);
		input_set.c_lflag &= ~(ECHO);
		input_set.c_cc[VMIN] = 1;
		input_set.c_cc[VTIME] = 0;
		input_set.c_cc[VINTR] = 0;
		first_once--;
	}
	return (&input_set);
}

static struct termios		*get_initial_termios(void)
{
	static struct termios	initial_set;
	static int				first_once = 1;

	if (first_once == 1)
	{
		tcgetattr(STDIN_FILENO, &initial_set);
		first_once--;
	}
	return (&initial_set);
}

static void					set_termios(int initial)
{
	struct termios			*setting;

	if (initial == TRUE)
		setting = get_initial_termios();
	else if (initial == FALSE)
		setting = get_input_termios();
	tcsetattr(STDIN_FILENO, TCSANOW, setting);
}

void						set_initial_termios(void)
{
	set_termios(TRUE);
}

void						set_input_termios(void)
{
	set_termios(FALSE);
}
