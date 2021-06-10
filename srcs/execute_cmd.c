/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:03:58 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/10 14:30:10 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** ulimit -aH  : maxProc 5568
** 0. execute_cmd.c
*/

/*
** 1. fork cmd on left side from pipe.
** 2. close write_fd from parent.
** 3. save read_fd to hand over to right side
*/

static int	execute_pipe_left(t_cmd *cmd, t_list *env, int *read_fd)
{
	int		pid;
	int		fd[2];

	cmd->read_fd = (*read_fd);
	if (-1 == pipe(fd))
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	cmd->write_fd = fd[1];
	pid = fork();
	if (pid == 0)
		execute_cmd2(cmd, env);
	close(fd[1]);
	*read_fd = fd[0];
	return (pid);
}

/*
** 1. fork cmd on right side from pipe.
*/

static int	execute_pipe_right(t_cmd *cmd, t_list *env, int read_fd)
{
	int		pid;

	cmd->read_fd = read_fd;
	pid = fork();
	if (pid == 0)
		execute_cmd2(cmd, env);
	return (pid);
}

/*
** 1. initialize variable to use.
*/

static void	init_var(int *i, int *read_fd, int (*pid)[10])
{
	int		idx;

	idx = 0;
	*i = 0;
	*read_fd = 0;
	while (idx < 10)
	{
		(*pid)[idx] = 0;
		idx++;
	}
}

/*
** 1. loop: execute cmd diffrently by the end type.
** 2. close read_fd after allocate.
** 3. loop wait child proc.
** 	3-1. get exit value from child. and change $? based on the value.
*/

void		execute_cmd(t_list *cmd, t_list *env)
{
	int		read_fd;
	int		pid[10];
	int		i;

	init_var(&i, &read_fd, &pid);
	while (cmd)
	{
		if (((t_cmd *)cmd->content)->end == e_pipe)
			pid[i] = execute_pipe_left((t_cmd *)cmd->content, env, &read_fd);
		else if ((t_cmd *)cmd->prev
		&& ((t_cmd *)cmd->prev->content)->end == e_pipe)
			pid[i] = execute_pipe_right((t_cmd *)cmd->content, env, read_fd);
		else
			execute_cmd2((t_cmd *)cmd->content, env);
		if (pid[i] == -1)
			print_errno();
		if (((t_cmd *)cmd->content)->read_fd != 0)
			close(((t_cmd *)cmd->content)->read_fd);
		cmd = cmd->next;
		i++;
	}
	wait_childs(pid);
}
