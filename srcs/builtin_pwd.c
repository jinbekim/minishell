/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:05:02 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/14 19:46:21 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	bt_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 1024);
	if (buf)
	{
		printf("%s\n", buf);
		free(buf);
		g_exitcode = 0;
		return (0);
	}
	g_exitcode = 1;
	return (1);
}
