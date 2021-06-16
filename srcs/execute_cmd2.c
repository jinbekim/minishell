/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:01 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/16 13:51:58 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	init_fd_argv(int read_fd, int write_fd, char ***argv)
{
	*argv = NULL;
	if (dup2(read_fd, 0) == -1)
	{
		print_errno();
		exit(1);
	}
	if (dup2(write_fd, 1) == -1)
	{
		print_errno();
		exit(1);
	}
}

static int	is_child(t_cmd *cmd)
{
	if (cmd->read_fd != 0 || cmd->write_fd != 1)
		return (1);
	else
		return (0);
}

void		execute_cmd2(t_cmd *cmd, t_list *env)
{
	char	**new_argv;
	t_list	*tmp;
	int		i_am_child;

	i_am_child = is_child(cmd);
	init_fd_argv(cmd->read_fd, cmd->write_fd, &new_argv);
	tmp = parse_cmd2(cmd->cmd, env);
	if (tmp == NULL)
	{
		if (is_child(cmd) == 0)
			return ;
		exit(1);
	}
	execute_cmd3(tmp, env, i_am_child);
}
