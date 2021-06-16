/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:04:20 by jinbekim          #+#    #+#             */
/*   Updated: 2021/06/15 20:23:12 by jinbekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
** 1. if fail to parsing
**      clear_cmd and return 0
*/

void	print_err_msg(char *cmd, char *arg)
{
	ft_putstr_fd("cash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
}

void	print_errno(void)
{
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	print_errno_exit(int status)
{
	print_errno();
	exit(status);
}

void	clear_cmd(t_list *cmd)
{
	t_list	*tmp;

	while (cmd)
	{
		free(((t_cmd *)(cmd->content))->cmd);
		((t_cmd *)cmd->content)->cmd = NULL;
		free(cmd->content);
		cmd->content = NULL;
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

t_list	*parse_fail(t_list *cmd)
{
	clear_cmd(cmd);
	return (0);
}
