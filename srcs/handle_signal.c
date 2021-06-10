/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:26 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:30:47 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void			handle_int(int sign)
{
	struct termios	diff;

	sign = 0;
	tcgetattr(0, &diff);
	if ((diff.c_lflag & ICANON) == ICANON)
		write(1, "\n", 1);
}

static void			handle_quit(int sign)
{
	struct termios	diff;

	tcgetattr(0, &diff);
	if ((diff.c_lflag & ICANON) == ICANON)
		printf("Quit: %d\n", sign);
}

void				handle_signal(void)
{
	signal(SIGINT, handle_int);
	signal(SIGQUIT, handle_quit);
}
