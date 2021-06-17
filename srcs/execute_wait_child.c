/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wait_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:13 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/17 11:32:47 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** exit_code == $?
*/

void	wait_child(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
		g_exitcode = 130;
	else if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
		g_exitcode = 131;
}

void	wait_childs(int pid[10])
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (pid[i] != 0)
			wait_child(pid[i]);
		else
			pid[i] = 0;
		i++;
	}
}
